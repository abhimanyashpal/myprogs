
#include <stdlib.h>
#include <stdio.h>

/**
 * In this problem we have to find the longest array
 * in which if we sort the elements we would get
 * a contigous sequence
 *
 * In the below eg we have a subarray [10 12 11]
 *
 * If we were to sort it then it would be contigous
 * however this is not the longest
 *
 * 
 * The other subarray [32 34 36 33 35 37]
 * is the longest
 *
 *
 * The trick is if you pick a subarray and if
 * the max element - min element + 1 is same
 * as the length of the subarray then this
 * subarray can be contigous and is a candidate
 * result.
 *
 *
 * Therefore we can enumerate through all 
 * subarrays and apply the above condition
 * to them to find the answer
 */

int a[] =  {10,12,11,94,56,32,34,36,33,35,37};

int res_len = -1;
int start_idx, end_idx;

void helper(int arr[], int start)
{
    int i = 0, j = 0, n = sizeof(a)/sizeof(int);
    int min = 32767, max = -32767;

    printf("\n");
    for (i = start; i < n; i++) {
        for (j = start; j <= i;j++) {
           printf("%d ",arr[j]);
           if (arr[j] < min) {
              min = arr[j];
           }

           if (arr[j] > max) {
             max = arr[j];
           }
        }

#if 0
        printf("\nSubarray length: %d Max: %d Min: %d",
                (i-start+1), max, min);
#endif
        if ((max - min + 1) == (i-start+1)) {
          /*
           * This means we have a sub-array if shuffled we will
           * get a contigous sequence
           */
		if ((i-start+1) > res_len) {
			res_len = (i-start+1);
                        start_idx = start;
                        end_idx = i;
                }
        }
        max = -32767;
        min = 32767;
        printf("\n");
    }
}

int main (int argc, char **argv)
{

  int n = sizeof(a)/sizeof(int);
  int i =0;

  for (i = 0; i < n; i++) {
	  helper(a, i);
  }

  printf("\n ===== CONTIGOUS SUBARRAY=====");

  if (res_len != -1) {
	  printf("\n Length : %d\n",res_len);
	  for (i = start_idx; i <= end_idx; i++) {
		  printf("%d ",a[i]);
	  }
  }
}
