#include <stdio.h>


void reverse (int *a, int s, int len)
{
    int e = 0,t;
    if (!a)
        return;

    if (len <= 0) {
        printf("\n Invalid length");
        return;
    }

    e = len - 1;

    while (s < e) {
      t = a[s];
      a[s] = a[e];
      a[e] = t;
      s++;
      e--;
    }
}

int main (int argc, char **argv)
{

   int a[] = {1,2,3,4,5};
   int num, idx, rot;

   num = sizeof(a)/sizeof(int);

   printf("\n Enter the number of times to rotate:");
   scanf("%d",&rot);

   if (rot >= num) {
       rot = rot - num;
   }

   if (!rot) 
       goto print_list;

   reverse(a,0,rot);
   reverse(a, rot, num);
   reverse(a,0,num);

print_list:
   for (idx = 0; idx < num; idx++) {
      printf("%d\t",a[idx]);
   }

   return 0;
}
     
