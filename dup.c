#include <stdio.h>

/*
 * Remove duplicates from the array.
 * Need to sort the array first and
 * move
 */
int a[] = {1,1,1,2,2,2,5,6,7,8,8,8,8};

int main (int argc, char **argv)
{
   int write_idx = 1;
   int i = 1; int n =13;

   while  (i < n) {
       if (a[i] != a[write_idx - 1]) {
           a[write_idx] = a[i];
           write_idx++;
       }
       i++;
   }

   while (write_idx < n) {
        a[write_idx++] = -1;
   }

   printf("\nDone.");
}
