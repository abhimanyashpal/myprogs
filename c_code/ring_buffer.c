#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char bool;

bool sigint_recvd;

typedef enum {
    INVAL_PARAM=1,
    FULL,
    EMPTY,
    SUCCESS
} status_t;

typedef struct cbuf_ {
    volatile unsigned long read;
    volatile unsigned long write;
    size_t num_elems;
    size_t elem_size;
    unsigned char *buf;
}cbuf_t;

typedef struct cbuf_stats_ {
    unsigned long long enq;
    unsigned long long deq;
    unsigned long long empty;
    unsigned long long full;
    unsigned long long fail_inval;
    unsigned long long split_wr;
    unsigned long long wr;
    unsigned long long split_rd;
    unsigned long long rd;
} cbuf_stats_t;

cbuf_stats_t stats;

#define INC_ENQ(e) stats.enq+=e
#define INC_DEQ(e) stats.deq+=e
#define INC_EMP()  stats.empty++
#define INC_FULL() stats.full++
#define INC_FAIL() stats.fail_inval++
#define INC_SPLIT_WR() stats.split_wr++
#define INC_WR() stats.wr++
#define INC_SPLIT_RD() stats.split_rd++
#define INC_RD() stats.rd++

cbuf_t *
create_buffer (size_t num_elems, size_t size_of_elem)
{
    cbuf_t *cbuf = malloc(sizeof(cbuf_t));

    if (!cbuf) 
      return NULL;

    if (num_elems & (num_elems - 1)) {
      printf("\nNos. of elements needs to be a power of 2.");
      return NULL;
    }

    cbuf->read = cbuf->write = 0;
    cbuf->num_elems = num_elems;
    cbuf->elem_size = size_of_elem;

    cbuf->buf = malloc(num_elems*size_of_elem);
    if (!cbuf->buf) {
      free(cbuf);
      return NULL;
    }
    bzero(cbuf->buf,num_elems*size_of_elem);

    return cbuf;
}

bool
isempty (cbuf_t *cbuf)
{
   return (cbuf->read == cbuf->write);
}

bool 
isfull (cbuf_t *cbuf)
{
   if (((cbuf->write + 1) & (cbuf->num_elems - 1)) == cbuf->read)
     return TRUE;

   return FALSE;
}

/**
 * Returns the number of free slots available.
 */
size_t
avail (cbuf_t *cbuf)
{
    if (cbuf->read == cbuf->write)
      return cbuf->num_elems - 1;

    if (cbuf->read > cbuf->write) {
        return (cbuf->read - cbuf->write - 1);
    }

    return (cbuf->num_elems - cbuf->write + cbuf->read - 1);
}

/**
 * Returns the current number of filled slots
 */
size_t
get_readable (cbuf_t *cbuf)
{
    if (cbuf->read == cbuf->write)
        return 0;

    if (cbuf->write >  cbuf->read) {
        return (cbuf->write - cbuf->read);
    }

    return (cbuf->num_elems - cbuf->read + cbuf->write);
}

/*
 * Enqueue a certain number of elements into the ring , with
 * each element being of the same size as that was passed when
 * the ring was created.
 */
status_t
enqueue (cbuf_t *cbuf, unsigned char *user_data, 
         size_t num_elems, size_t *succ_elems)
{
  size_t available,num_write,num_rem;
  unsigned long w;
  unsigned char *write_ptr;

  if (!cbuf || !num_elems || !succ_elems) {
    INC_FAIL();
    return INVAL_PARAM;
  }

  if (isfull(cbuf)) {
    INC_FULL();
    return FULL;
  }

  /*
   * Figure out the number of available slots and if the user is
   * requesting to write into more slots than that are available
   * then we will truncate the number of elements that will be 
   * written
   */
  available = avail(cbuf);

  if (num_elems > available) {
    num_elems = available;
  }

  //Read the current write location
  w = cbuf->write;

  //Test the wrap condition
  if ((w + num_elems) > cbuf->num_elems) {

      //Number of elements to be written till the end
      num_write = cbuf->num_elems - w;

      //Balance number of elements to be written after a wrap
      num_rem = num_elems - num_write;

      //Set the pointer to where we should starting writing
      write_ptr = &cbuf->buf[w*cbuf->elem_size];

      //Write all the way till the end of the ring
      memcpy(write_ptr, user_data, num_write*cbuf->elem_size);

      //Wrap it (We could just set it to 0 as well)
      w = (w + num_write) & (cbuf->num_elems - 1);

      //Advance to user pointer to point to the remaining data
      user_data = user_data + (num_write*cbuf->elem_size);

      //Set the approriate write
      write_ptr = &cbuf->buf[w*cbuf->elem_size];

      //Write rest of the data
      memcpy(write_ptr, user_data, num_rem*cbuf->elem_size);

      //Update the write index
      w = (w + num_rem) & (cbuf->num_elems - 1);

      INC_SPLIT_WR();

    } else {

      //No wrap , perform regular copy
      memcpy (&cbuf->buf[w*cbuf->elem_size], 
             user_data, 
             num_elems*cbuf->elem_size);
      w= (w + num_elems) & (cbuf->num_elems - 1);
      INC_WR();
    }

    //Barrier needed here

    //Update the write index the ring

    cbuf->write = w; 

    *succ_elems = num_elems;

    INC_ENQ(*succ_elems);
 
    return SUCCESS;
}

status_t
dequeue (cbuf_t *cl_buf, unsigned char *user_data, 
         size_t req_elems, size_t *deq_elems)
{
    unsigned long r;
    size_t readable_slots, num_read, num_rem;
    unsigned char *read_ptr;

    if (!cl_buf || !user_data || req_elems > cl_buf->num_elems || !deq_elems) {
      INC_FAIL();
      return INVAL_PARAM;
    }

    if (isempty(cl_buf)) {
      INC_EMP();
      return EMPTY;
    }

    readable_slots = get_readable(cl_buf);
    if (readable_slots < req_elems) {
      req_elems = readable_slots;
    }

    //Cache the current read pointer
    r = cl_buf->read;

    if ((r + req_elems) > cl_buf->num_elems) {
      //Split read case
      num_read = cl_buf->num_elems - r;
      num_rem = req_elems - num_read;

      //Read till the end of ring
      read_ptr = &cl_buf->buf[r * cl_buf->elem_size];
      memcpy (user_data, read_ptr, num_read*cl_buf->elem_size);

      //Advance user data and set the new read to beginning of ring
      r = (r + num_read) & (cl_buf->num_elems - 1);
      user_data = user_data + (num_read*cl_buf->elem_size);

      //Read the remaining bytes
      read_ptr = &cl_buf->buf[r * cl_buf->elem_size];
      memcpy (user_data, read_ptr, num_rem*cl_buf->elem_size);

      //Advance the remaning
      r = (r + num_rem) & (cl_buf->num_elems - 1);

      INC_SPLIT_RD();
    } else {
      memcpy(user_data, &cl_buf->buf[r * cl_buf->elem_size],
             req_elems * cl_buf->elem_size);
      r = (r + req_elems) & (cl_buf->num_elems - 1);
      INC_RD();
    }

    //Barrier
  
    cl_buf->read = r;

    *deq_elems = req_elems;

    INC_DEQ(*deq_elems);
 
    return SUCCESS;
}

#define DBUF_SZ 48
unsigned char dbuf[DBUF_SZ] = { 
                           0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
                           0x2a, 0x2b, 0x3c, 0x2d, 0x2e, 0x2f,
                           0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
                           0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
                           0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
                           0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
                           0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
                           0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
                         };

#define SLEEP_INTVL_US SLEEP_INTVL*1000
#define SLEEP_INTVL 100 //ms
#define SLEEP_INTVL_US_CONS SLEEP_INTVL_CONS*1000
#define SLEEP_INTVL_CONS 100 //ms
#define LOCAL_BUF_SZ 512

void *
consumer (void *data)
{
    cbuf_t *cl_buf = (cbuf_t *)data;
    unsigned long elem_sz,i,elem_idx,elems;
    unsigned char buf[LOCAL_BUF_SZ];
    size_t succ_elems = 0;
    status_t ret_val;

    if (!cl_buf) {
        printf("\nNo ring buffer created...");
        return NULL;
    } else {
        printf("\nElement_sz: %lu Num_elems: %lu\n", 
                 cl_buf->elem_size, cl_buf->num_elems);
        fflush(stdout);
    }

    elem_sz = cl_buf->elem_size;

    while (1 && !sigint_recvd) {
        /*
         * Dequeue data from queue
         */
        elems = rand()%cl_buf->num_elems;

        ret_val = dequeue(cl_buf, buf, elems, &succ_elems);
        if (ret_val != SUCCESS) {
            if (ret_val == EMPTY) {
              printf("\nRing empty....\n");
              fflush(stdout);
            }
        } else {
            printf("\nDeq_req: %lu Deq_succ: %lu elements...\n",elems, succ_elems);
            //Debug dump
            i = 0;
            while (i < succ_elems*cl_buf->elem_size) {
                printf("%02x ", buf[i]);
                i++;
            }
        }
        fflush(stdout);
        usleep(SLEEP_INTVL_US_CONS);
    }
    return NULL;
}

void *
producer (void *data)
{
    cbuf_t *cl_buf = (cbuf_t *)data;
    unsigned int elem_sz,i,elem_idx,elems;
    unsigned char buf[LOCAL_BUF_SZ];
    size_t succ_elems = 0;
    status_t ret_val;

    if (!cl_buf) {
        printf("\nNo ring buffer created...");
        return NULL;
    } else {
        printf("\nElement_sz: %lu Num_elems: %lu\n", 
                 cl_buf->elem_size, cl_buf->num_elems);
        fflush(stdout);
    }

    elem_sz = cl_buf->elem_size;

    while (1 && !sigint_recvd) {
        /*
         * Generate some data
         */
        elems = rand()%cl_buf->num_elems;

        if (elems * cl_buf->elem_size > LOCAL_BUF_SZ) {
          printf("\nToo many elems - Insufficient local buffer Skipping enqueue...");
          continue;
        }
          
        bzero(buf,sizeof(buf));

        elem_idx = 0;
        while (elem_idx < elems) {
            elem_sz = cl_buf->elem_size;
            /*
             * Just pick random bytes from our DBUF
             */
            i = elem_idx*elem_sz; //Starting index
            while (elem_sz)  {
                buf[i++] =  dbuf[rand()%DBUF_SZ];
                elem_sz--;
            }
            elem_idx++;
        }

        ret_val = enqueue(cl_buf, buf, elems, &succ_elems);
        if (ret_val != SUCCESS) {
          if (ret_val == FULL) {
            printf("\nBuffer is full !!! \n");
          }
        } else {
            printf("\nEnq_req %u elems, enqueued %lu elems\n", elems, succ_elems);
        }
        //Debug dump
        i = 0;
        while (i < elems*cl_buf->elem_size) {
            printf("%02x ", buf[i]);
            i++;
        }
    
        fflush(stdout);
        usleep(SLEEP_INTVL_US);
    }

    return NULL;
}   

pthread_t prod_th;
pthread_t cons_th;

void
sigint_hdlr (int d)
{
   sigint_recvd = 1;
}

void
show_stats(cbuf_t *cl_buf)
{
  printf("\nStats");
  printf("\n=====");
  printf("\n%-10s %-8llu","Enq",stats.enq);
  printf("\n%-10s %-8llu","Deq",stats.deq);
  printf("\n%-10s %-8llu","Empty",stats.empty);
  printf("\n%-10s %-8llu","Full",stats.full);
  printf("\n%-10s %-8llu","Fail",stats.fail_inval);
  printf("\n%-10s %-8llu","split-wr",stats.split_wr);
  printf("\n%-10s %-8llu","reg-wr",stats.wr);
  printf("\n%-10s %-8llu","split-rd",stats.split_rd);
  printf("\n%-10s %-8llu","reg-rd",stats.rd);
  printf("\n%-10s %-8lu","Available",avail(cl_buf));
  printf("\n%-10s %-8lu","Readable",get_readable(cl_buf));

}

int main (int argc, char **argv)
{
    cbuf_t *cl_buf = create_buffer(64,4);
    size_t num_elems;
    unsigned char buf[256];

    if (!cl_buf)
      return 0;

    signal(SIGINT, sigint_hdlr);

    if (pthread_create(&prod_th, NULL, producer, (void *)cl_buf) != 0) {
      printf("\nFailed to create producer....");
    }

    if (pthread_create(&cons_th, NULL, consumer, (void *)cl_buf) != 0) {
      printf("\nFailed to create ....");
    }

    pthread_join(cons_th,NULL);
    pthread_join(prod_th,NULL);

    show_stats(cl_buf);
}
