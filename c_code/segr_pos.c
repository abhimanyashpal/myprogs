#include <stdio.h>

/**
 * Segragates a array arong a pivot value. In this case the pivot value is 0
 */

void swap (int *a, int *b)
{
    int temp;

    temp  = *a;
    *a = *b;
    *b = temp;
}

static void printarr (int arr[], int n)
{
    int i;

    printf("\n");
    for (i = 0; i < n; i++) {
       printf("%d ",arr[i]);
    }
    printf("\n");
}

static void 
segregate_pos (int arr[], int n)
{
    int pidx = 0;
    int i,pivot = 0;

    for (i = 0; i < n; i++) {
       if (arr[i] < pivot) {
           swap(&arr[i], &arr[pidx]);
           pidx++;
       }
    }
}

int main (int argc, char **argv)
{
   int arr[] = {5, 9 , 7, 4, 3, 11, 2}
   int n = sizeof(arr)/sizeof(arr[0]);

   segregate_pos(arr, n);

   printarr(arr, n);
}

