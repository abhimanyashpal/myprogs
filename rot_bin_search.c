#include <stdio.h>
#include <stdlib.h>

int arr[] = {6,1,2,3,4,5};
//int arr[] = {2,3,4,5,6,1};
//int arr[] = {10,20,1,3,6,7,8};
//int arr[] = {1,2,3,5,6,7,8};
//int arr[] = {0,1};


int
find_pivot (int arr[], int n)
{
    int l = 0, u = n-1, mid = 0;

    mid = l + (u-l)/2;

     while (l < u) {
        if (u-l <= 1) {
            if (arr[u] < arr[l]) {
                return u;
            } else {
                return -1;
            }
        }

        if (arr[mid] > arr[mid+1]) {
          return (mid+1);
        } else if (arr[mid-1] > arr[mid]) {
          return mid;
        } 

        if (arr[l] < arr[mid]) {
            l = mid+1;
        } else {
            u = mid-1;
        }
        mid = l + (u-l)/2;
    }

    return -1;
}

int
rot_bin_search (int arr[], int n, int key)
{
    int l = 0, u = n-1, mid = 0;

    if (n == 1) {
        if (arr[0] == key)
            return 0;
        else
            return -1;
    }

    if (n == 2) {
       if (arr[0] == key)
           return 0;
       else if (arr[1] == key)
           return 1;
       else
           return -1;
    }
 
    mid = l + (u-l)/2;

    while (l < u) {
        /*
         * Check if mid is the key
         */
        if (arr[mid] == key)
            return mid;

        if (arr[l] < arr[mid]) {
            /*
             * No hole in lower half
             */
            if (key >= arr[l] && key < arr[mid]) {
                u = mid-1;
            } else {
                l = mid+1;
            }
        } else {
            /*
             * No hole in right half
             */
            if (key > arr[mid] && key <= arr[u]) {
                l = mid+1;
            } else {
                u = mid - 1;
            }
         }
        mid = l + (u-l)/2;
    }

    if (l == u) {
        if (arr[l] == key)
            return l;
    }

    return -1;
}

int main (int argc, char **argv)
{
    int pos = -1;
    int key = 1;
    int n = sizeof(arr)/sizeof(arr[0]);

    pos = rot_bin_search(arr,n,key);

    if (pos >= 0) {
        printf("\nElement found at position index %d",pos);
    } else {
        printf("\n Element not found");
    }

    printf("\n PIVOT : %d",find_pivot(arr,n));
}
