
#include <stdio.h>

int arr[] = {7,6,5,4,3,2,1};

int
partition (int arr[], int start, int end)
{

  int pindex = start;
  int temp, pivot = arr[end]; //can be randomized
  int i;

  for (i = start; i < end; i++) {
       if (arr[i] <= pivot) {
           temp = arr[i];
           arr[i] = arr[pindex];
           arr[pindex] = temp;
           pindex++;
       }
  }

  temp = arr[end];
  arr[end] = arr[pindex];
  arr[pindex] = temp;

  return pindex;
}

void
quicksort(int arr[], int start, int end)
{
   int pindex;

   if (start < end) {
       pindex = partition(arr, start, end);
       quicksort(arr, start, pindex - 1);
       quicksort(arr, pindex+1, end);
   }
}

void
printarr (int a[], int len)
{
   int i;

   for (i=0;i<len;i++)
      printf("\n %d",a[i]);
}

int 
main (int argc, char **argv) {

    int len = sizeof(arr)/sizeof(int);

    printf("\n len: %d",len);
    quicksort(arr,0,len-1);

    printarr(arr,len);
}
