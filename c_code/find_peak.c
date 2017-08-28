
/*
 * Find a peak element in the array
 *
 * Eg: {1,4,3,6,7,5}
 *
 * 4 is the peak element in this array
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Keep checking adjacent values.
 * This is O(n)
 */
int find_peak_naive (int arr[], int n)
{
    int i;

    if (n == 0)
        return -1;

    if (n == 1)
        return arr[0];

    /*
     * Compare the starting edge and be done with it
     */
    if (arr[0] > arr[1])
        return arr[0];


    /*
     * Check reset of array
     */
     i = 1;

     while (i < n-1) {
         if (arr[i] > arr[i-1] && arr[i] > arr[i+1])
             return arr[i];

         i++;
     }

    /*
     * Compare ending edge
     */
    if (arr[i] > arr[i-1])
        return arr[i];

     return -1;
}

/*
 * O(log n)
 */
int find_peak_bin (int arr[], int n)
{
   int l = 0, u = n-1;
   int m = 0;

    if (n == 0)
        return -1;

    if (n == 1)
        return arr[0];

    /*
     * Compare the starting edge and be done with it
     */
    if (arr[0] > arr[1])
        return arr[0];


    while (l < u) {
       /*
        * Only 2 elements are left
        */
       if ((u - l) == 1) {

           if ((l == 0) || (u == n-1)) { 
               if (arr[l] > arr[u])
                   return arr[l];
               else if (arr[l] < arr[u])
                   return arr[u];
               else 
                   return -1;
           } else {
               return -1;
           }
       }
    
        m = (l+u)/2;

        if (arr[m] > arr[m-1] && arr[m] > arr[m+1]) {
            return arr[m];
        } else if (arr[m] < arr[m-1]) {
           /*
            * I am smaller than the person on the left, so
            * he could be the peak and hence we will move to
            * the left
            */
            u = m-1;
        } else {
            /*
             * Symmetric condition
             */
            l = m+1;
        }
    }

    if (u == l) {
       if (u == 0) {
           if (arr[0] > arr[1])
               return arr[0];
       } else if (u == n-1) {
          if (arr[u] > arr[u-1])
              return arr[u];
       }
    }

    return -1;
}




int main (int argc, char **argv)
{
    //int arr[] = {1,4,3,6,7,5};
    //int arr[] = {1,2,3,6,7,5};
    int arr[] = {1,2,3,6,7,8};
    int n = sizeof(arr)/sizeof(int);
    int peak = -1;

    //peak = find_peak_naive(arr,n);
    peak = find_peak_bin(arr,n);

    printf("\nPeak: %d",peak);
}
