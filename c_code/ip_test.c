#include <stdio.h>
#include <stdlib.h>


static void
print_ip (unsigned long x)
{
  unsigned char buf[4];

  buf[0] = x >> 24;
  buf[1] = ((x >> 16) & 0xff);
  buf[2] = ((x >> 8) & 0xff);
  buf[3] = x;

  printf("\n%d.%d.%d.%d\n",buf[0], buf[1], buf[2], buf[3]);
}
  
int main (int argc , char **argv)
{
    unsigned long x = 0xaabbccdd;

    print_ip(x);
}
