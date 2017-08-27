#include <stdio.h>

/**
 * Dutch national flag problem in which we have to partition 
 * an array around a pivot value. Everything less than the pivot
 * goes to the left.
 * Everything equal to the pivot stays in the middle.
 * Everything greater than the pivot goes to the right.
 */

void swap (int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void printarr(int arr[], int n)
{
    int i = 0;

    while (i < n) {
        printf("\n%d",arr[i++]);
    }
}

void dutch_part(int arr[], int n)
{
    int small=0,equal =0, large = n-1;
    int pivot = 1;

    while (equal <= large) {
        if (arr[equal] < pivot) {
            swap(&arr[small],&arr[equal]);
            small++;
            equal++;
        } else if (arr[equal] == pivot) {
             equal++;
        } else {
            swap(&arr[large],&arr[equal]);
            large--;
        }
    }
}

void partition (int arr[], int s , int e)
{
    int pidx = s;
    int i, pivot = 1;

    for (i = s; i < e; i++) {
        if (arr[i] <= pivot) {
          swap(&arr[i], &arr[pidx]);
          pidx++;
        }
    }

    printf("\n PIDX: %d",pidx);
}

int main (int argc, char **argv)
{
    int arr[12] =  {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("\n NUMBER OF ELEM %d",n);
    dutch_part(arr, n);
    //partition(arr,0,n);
    printf("\n DONE PARTITION");
    printarr(arr,n);
}
