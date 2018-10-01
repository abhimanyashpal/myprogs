#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

void 
dump_ips(unsigned long ip, unsigned long count);

void 
dump_ips(unsigned long ip, unsigned long count)
{
    char buf1[256];
    unsigned long oip;
    int i;

    ip = ntohl(ip);
    i = 0;
    while (i < count) {
        ip++;
        oip = htonl(ip);
        inet_ntop(AF_INET, &oip, &buf1[0],256);
        printf("\n %s \n",buf1);
        i++;
    }
        
}


typedef struct ip_pool_cfg_ {
    unsigned long base_ip;
    unsigned int count;
} ip_pool_cfg_t;

ip_pool_cfg_t user_cfg;

typedef struct bmap_handle_ {
    unsigned int *bmap;
    unsigned int bmap_word_sz;
    unsigned int cur_pos;
} bmap_handle_t;

unsigned long alloc;
unsigned long alloc_fail;
unsigned long free_cnt;


#define ALIGN_SZ 32
#define WORD_SZ sizeof(unsigned int)
#define NBBW (WORD_SZ*NBBY)

bmap_handle_t *
init_bitmap (int count)
{
    bmap_handle_t *bmp_h = NULL;
    unsigned int bmap_word_sz = 0;

    if (!count) {
      printf("\nInvalid count, unable to init bitmap");
      return NULL;
    }

    //Align to 32
    if (count & (ALIGN_SZ - 1)) {
      count = (count + ALIGN_SZ - 1) & ~(ALIGN_SZ - 1);
    }
    printf("\nAligned bits: %u\n",count);
    bmap_word_sz = count/(WORD_SZ*8); 

    //Allocate the handle
    bmp_h = malloc(sizeof(*bmp_h));
    if (!bmp_h) {
      printf("\nFailed to alloc handle....");
      return NULL;
    }
    

    //Allocate the internals
    bmp_h->bmap  = malloc(bmap_word_sz * WORD_SZ);
    if (!bmp_h->bmap) {
      printf("\nFailed to alloc bitmap");
      return NULL;
    }
    memset(bmp_h->bmap,0x0,bmap_word_sz * WORD_SZ);
    bmp_h->bmap_word_sz = bmap_word_sz;
    bmp_h->cur_pos = 0;

    return bmp_h;
}

static unsigned long
get_ip (bmap_handle_t *bmp_h)
{
    unsigned char bit_pos;
    unsigned int start_pos;
    unsigned int *curr_word = &bmp_h->bmap[bmp_h->cur_pos];
    unsigned long ret_ip;

    start_pos = bmp_h->cur_pos;
    while (1) {
       
        for (bit_pos = 0; bit_pos < NBBW; bit_pos++) {
            if (!(*curr_word & (1 << bit_pos)))
              break;
        }

        //Found a bit position in the current word
        if (bit_pos != NBBW)
          break;  

        //Move to the next word
        bmp_h->cur_pos = (bmp_h->cur_pos + 1) % bmp_h->bmap_word_sz;
        curr_word = &bmp_h->bmap[bmp_h->cur_pos];

        //If all bits are set then no space available
        if (bmp_h->cur_pos == start_pos) {
          //printf("\nNo bits available !!!!!!!");
          alloc_fail++;
          return 0;
        }
    }

    printf("\nFound free bit %u curr_pos:%u",bit_pos,bmp_h->cur_pos);

   *curr_word |= (1 << bit_pos);

   ret_ip = user_cfg.base_ip + (bmp_h->cur_pos*NBBW + bit_pos);

   //If we have set the MSB then we update the current position to
   //be tested   
   if (bit_pos == NBBW-1) {
     bmp_h->cur_pos = (bmp_h->cur_pos + 1) % bmp_h->bmap_word_sz;
   }

   alloc++;
   return (ret_ip);
}

static void
return_ip (bmap_handle_t *bmp_h, unsigned long free_ip)
{
    unsigned int offset = free_ip - user_cfg.base_ip;
    unsigned int word = offset/NBBW;
    unsigned int bit_pos = offset%NBBW;

    bmp_h->bmap[word] &= ~(1 << bit_pos);
    free_cnt++;
}

void test_get_ip (bmap_handle_t *h, unsigned int count)
{
    char buf1[256];
    unsigned long oip,ip;
    unsigned int i;
    int free_count = 10;
    int r = 0;

    i = 0;
    while (i < count) {
	ip = get_ip(h);
	if (!ip) {
	  i++;
	  continue;
	}

	oip = htonl(ip);
	inet_ntop(AF_INET, &oip, &buf1[0],256);
	printf("\n %s \n",buf1);

        //Randomly free some ip's
        if (free_count > 0) {
          r = rand();

          if (!(r%5)) {
            r = r%user_cfg.count;
            return_ip(h,user_cfg.base_ip + r);
          }

          //free_count--;
        }
	i++;
    }
}

int main (int argc, char **argv)
{
    int ret = 0;
    unsigned long count = 0;
    unsigned long base_ip;
    bmap_handle_t *bmp_h = NULL;

    if (argc != 3) {
      printf("\nError - Please enter in the following format - "
	     "<progname> a.b.c.d <ip-count>");
      return -1;
    }

    ret = inet_pton(AF_INET,argv[1],&base_ip);
    if (!ret) {
      printf("\n INVALID IP address");
      return -1;
    }

    count = strtoul(argv[2], NULL, 10);

    printf("\n Base_ip: 0x%08lx",base_ip);
    printf("\n Count: %lu\n",count);

    if (count >= 65536) {
      printf("\n Count exceeds limit of 64K\n");
      return -1;
    }

    //dump_ips(base_ip, count);

    user_cfg.base_ip = ntohl(base_ip); //Save in network order always
    user_cfg.count = count;
    bmp_h = init_bitmap(count);

    test_get_ip(bmp_h, 65000);

    printf("\nAllocs: %lu Free: %lu Fail: %lu\n",alloc,free_cnt, alloc_fail);
}
