#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u_int8_t;

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

static void
hexdump (u_int8_t *buf, unsigned int len)
{
    unsigned int chunks, start, end, rem;
    unsigned int chunk_id;

    if (!buf)
        return;
   
    chunks = len/16;
    rem = len%16;

    chunk_id = 0;
    while (chunk_id < chunks) {
        start = chunk_id * 16;
        end   = start+16;

        printf("\n0x%02x:",start);
        while (start < end) {
            printf("%02x ",buf[start]);
            start++;
        }
        chunk_id++;
    }

    if (!rem)
        return;

    start = chunk_id * 16;
    printf("\n0x%02x:",start);

    while (rem) {
        printf("%02x ",buf[start]);
        start++;
        rem--;
    }

    printf("\n");
}

int main (int argc, char **argv)
{
    unsigned int len = sizeof(test_buf)/sizeof(test_buf[0]);

    printf("\nBuffer size: %u",len);

    hexdump(test_buf, len);
}