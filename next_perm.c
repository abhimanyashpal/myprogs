#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
get_next_perm_str (char *arr, int n)
{
    int i,start,end,pivot,pidx,t;

    /*
     * 1.) Find the the non-decreasing suffix.
     */
    i = n-1;
    while (i > 0) {
        if (arr[i] > arr[i-1])
            break;
        i--;
    }

    if (i == 0) {
        printf("\n No next permutation possible");
        return;
    }

    /*
     * Logically we have a prefix and a Suffix now
     */
    pivot = arr[i-1]; // This is the first elemet from the right which was lesser
                      // than the suffix
    pidx = i-1;

    /*
     * 2.) Find the first element in the suffix which is greater than the pivot
     */
    while (i < n) {
        if (arr[i] < pivot) {
          // That means arr[i-1] was the first person greater than the pivot
          t = arr[i-1];
          arr[i-1] = pivot;
          arr[pidx] = t;
          break;
        }
        i++;
    }

    if (i == n) {
        // Swap with rightmost
          t = arr[n-1];
          arr[n-1] = pivot;
          arr[pidx] = t;
    }

   /*
    * 3.) Reverse the Suffix portion of the array
    */
   start = pidx+1;
   end = n-1;
   while (start < end) {
       t = arr[start];
       arr[start] = arr[end];
       arr[end] = t;
       start++;
       end--;
   }
}


void
get_next_perm (int arr[], int n)
{
    int i,start,end,pivot,pidx,t;

    /*
     * 1.) Find the the non-decreasing suffix.
     */
    i = n-1;
    while (i > 0) {
        if (arr[i] > arr[i-1])
            break;
        i--;
    }

    if (i == 0) {
        printf("\n No next permutation possible");
        return;
    }

    /*
     * Logically we have a prefix and a Suffix now
     */
    pivot = arr[i-1]; // This is the first elemet from the right which was lesser
                      // than the suffix
    pidx = i-1;

    /*
     * 2.) Find the first element in the suffix which is greater than the pivot
     */
    while (i < n) {
        if (arr[i] < pivot) {
          // That means arr[i-1] was the first person greater than the pivot
          t = arr[i-1];
          arr[i-1] = pivot;
          arr[pidx] = t;
          break;
        }
        i++;
    }

   /*
    * 3.) Reverse the Suffix portion of the array
    */
   start = pidx+1;
   end = n-1;
   while (start < end) {
       t = arr[start];
       arr[start] = arr[end];
       arr[end] = t;
       start++;
       end--;
   }
}

int main (int argc, char **argv)
{
    int arr[] = {0,1,2,5,3,3,0};
    int n = 7,i;
    char buf[100]; int len = 0;

    get_next_perm(arr,n);

    i = 0;
    printf("\n");
    while (i < n) {
        printf("%d ",arr[i]);
        i++;
    }

    printf("\n Enter String:");
    scanf("%s",buf);

    get_next_perm_str(&buf[0],strlen(buf));

    printf("\n %s",buf);
}
