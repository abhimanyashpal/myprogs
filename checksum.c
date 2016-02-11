#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u_int8_t;
typedef unsigned int u_int32_t;
typedef unsigned char boolean;

#define TAIL_ROOM 8
#define TRUE 1
#define FALSE 0

u_int8_t test_buf[] = {
0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00, 
0x00,0x00,0x00,0xff,0x01,0x00,0x00,0x00,        
0x02,0x00,0x00,0x00,0x00,0x00,0x40,0x00,
0x00,0x00,0x00,0x00,0x00,0x10,0x3c,0x00,        
0x00,0x54,0x00,0x02,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x22,0x00,0x00,0x77,0x80,        
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
0xff,0xff,0xff,0xff,0xdc,0x38,0xe1,0x69,        
0xff,0xe8,0x08,0x06,0x00,0x01,0x08,0x00,
0x06,0x04,0x00,0x01,0xdc,0x38,0xe1,0x69,        
0xff,0xe8,0x66,0x00,0x01,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0x00,0x01,0x01,        
0xa8,0xd0};

static
void sim_corruption (u_int8_t *buf, u_int32_t offset)
{
    int i = 0;
    //Do some error checking later

    u_int8_t *new = buf + offset;

    while (i < 64) {
      *new = 0xff;
       new++;
       i++;
    }
}

static boolean
calc_checksum (u_int8_t *buf, u_int32_t buf_len)
{
   u_int32_t i = 0;
   u_int32_t sum = 0;

   while (i < buf_len) {
       if (i & 1) {
           sum += buf[i];
       } else {
           sum += (buf[i] << 8);
       }
       i++;
   }

   while (sum & 0xffff0000) {
     sum = (sum >> 16) + (sum & 0xffff);
   }

   printf("\nCalculated checksum : 0x%x",sum);

   /*
    * Since we have done ~sum during the calculation, 
    * when we compute the sum over the whole data
    * including the transmited frame then the value
    * will be 0xffff
    */
   if (sum == 0xffff)
       return TRUE;
   else
       return FALSE;
}

/*
 * Compute a 16-bit checksum
 */
static u_int32_t
fill_checksum (u_int8_t *buf, u_int32_t buf_len)
{
	u_int32_t i =0;
	u_int32_t sum = 0x0;

	for (i = 0; i < buf_len; i += 2) {
		sum += (buf[i+1] << 8) + buf[i];
	}

	while (sum & 0xffff0000) {
		sum = (sum >> 16) + (sum & 0xffff);
	}

	sum = ~sum;

	printf("\nChecksum : 0x%x \n", (sum & 0xffff));

	buf[buf_len++] = sum;
	buf[buf_len++] = sum >> 8;

        return buf_len; //New length

}

static u_int8_t *
generate_stream (unsigned int buf_len)
{
    u_int8_t mod3[3] = {0xab, 0xcd, 0xde};
    u_int8_t *buf = NULL, *fill = NULL;
    int i = 0;

    buf_len += TAIL_ROOM;

    buf = malloc(buf_len);
    if (!buf) {
        printf("\n Failed to allocate stream.");
        return NULL;
    }

    memset(buf, 0x0, buf_len);

    fill = buf;

    while (i < buf_len) {
       *fill = mod3[i%3];
        fill++;
        i++;
    }

    return buf;
}

static void
dump_stream (uint8_t *buf, int len)
{
   char dis[256];
   char *disp = &dis[0];
   u_int32_t offset = 0,idx = 0, num = 0, num_to_print = 0;

   memset(&dis[0], 0 , sizeof(dis));

   while (offset < len) {

     num = sprintf(disp,"0x%02x:",offset);

     disp = disp + num;

     num_to_print = (len - offset);
     if (num_to_print > 16)
         num_to_print = 16;

     idx = 0;
     while (idx < num_to_print) {
       num = sprintf(disp, "%02x ",*buf);
       buf++;
       disp = disp + num;
       idx++;
     }
     printf("\n%s",dis);
    
     memset(&dis[0], 0 , sizeof(dis));
     disp = &dis[0];
     num = 0;
     idx = 0;

     offset += 16;
   }

   printf("\n");
}

int main (int argc, char **argv)
{
  unsigned long len = 0x0, new_len = 0x0;
  u_int8_t *buf = NULL;

  if (argc < 2) {
      printf("\n <exe> <len>");
      return -1;
  }

  len = strtoul(argv[1], NULL, 10);

  if (len & 0x1) {
      printf("\nOdd len");
      len++;
  }

  buf = generate_stream(len);
  if (!buf)
    return -1;

  printf("\nDumping pattern without checksum");
  printf("\n================================\n");
  if (buf) {
      dump_stream(buf, len);
  }

  new_len = fill_checksum(buf, len);

  printf("\nDumping pattern WITH checksum");
  printf("\n================================\n");
  if (buf) {
      dump_stream(buf, new_len);
  }

  printf("\nChecksum valid : %s \n",calc_checksum(buf,new_len) ? "Yes" : "No");

  new_len = fill_checksum(test_buf, 96);
  dump_stream(test_buf,98);
  printf("\nChecksum valid : %s \n",calc_checksum(test_buf,98) ? "Yes" : "No");

  sim_corruption (&test_buf[0], 16);
  dump_stream(test_buf,98);
  printf("\nChecksum valid : %s \n",calc_checksum(test_buf,98) ? "Yes" : "No")
}
