#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Find a subarray which matches a target sum
 */

int arr[] = {1,2,3,2,1,1,2,3,3};

void
subarray_sum (int arr[], int n, int target_sum)
{
    int start = 0, end = 1;
    int curr_sum = 0;

    curr_sum = arr[start];

    while (end < n) {
        if (curr_sum == target_sum) {
          printf("\n Sum found at start: %d end: %d",start,end-1);
          curr_sum -= arr[start];
          start++;
        } else if (curr_sum < target_sum) {
          curr_sum += arr[end];
          end++;
        } else {
          curr_sum -= arr[start];
          start++;
        }
    }
}

int main (int argc, char **argv)
{
   int n = sizeof(arr)/sizeof(arr[0]);

   subarray_sum(arr,n,6);
}
   
