#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//return index of the max element
int getmax (int arr[], int start, int end)
{
    int imax = -1, max = -1;

    if (start > end)
        return -1;

    if (start == end)
        return start;

    while (start <= end) {
       if (arr[start] > max) {
           max = arr[start];
           imax = start;
       }
       start++;
    }

    return imax;
}

// return the min
int getmin (int arr[], int start, int end)
{
    int imin = -1, min = INT_MAX;

    if (start > end)
        return -1;

    if (start == end)
        return start;

    while (start < end) {
       if (arr[start] <  min) {
           min = arr[start];
           imin = start;
       }
       start++;
    }

    return imin;
}

void reverse (int arr[], int start, int end)
{

  int temp;

  while (start < end) {
    temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
    start++;
    end--;
  }
}

/*
 * Pancake sorting is based on doing a flip.
 */
int main (int argc, char **argv)
{
    int arr[] = {1,9,2,2,6,8,3};
    int i,imax, n = 7;

    for (i = n-1;i > 0; i--) {
       imax = getmax(arr,0,i);

       /*
        * Flip once so that the biggest comes on top
        */
       reverse(arr,0,imax);

       /*
        * Flip complete array so that biggest comes at the bottom
        */
       reverse(arr,0,i);
    }

    for (i = 0; i < n; i++) 
       printf("\n %d",arr[i]);

    return 0;
}
