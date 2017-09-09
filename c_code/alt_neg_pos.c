#include <stdlib.h>
#include <stdio.h>

/**
 * We need arrange the below array with positive numbers at even
 * indices and negative at odd indices
 *
 * Expected output for the below array will be,
 *
 * [ 3 -1 2 -6 4 -9 5 7]
 */

/*
 * The trick to solve this problem is the concept of
 * right rotation of a subarray
 *
 * So what we do is for every element, if it is
 * not present in the correct position then 
 * we move forward and look for an element with the
 * opposite sign.
 *
 * Now we perform a right rotation of that subarray so
 * that the number with the opposite sign will end
 * up coming in the correct position
 */

int arr[] =  {-1,3,2,4,5,-6,7,-9};

void reverse (int arr[], int start , int end)
{
    int temp;

    //printf("\n s: %d e: %d\n",start, end);
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void right_rotate (int arr[])
{
    //Rotate the arry to the right by 1
    int k = 1;
    int n = sizeof(arr);

    printf("\n %d \n",n);
    reverse(arr, 0, n-k-1);
    reverse(arr, n-k, n-1);
    reverse(arr, 0, n-1);
}

void right_rotate_subarray (int arr[], int s, int e)
{
    int k = 1;
    int n = (e - s + 1);
    reverse(arr, s, (s+n-2));
    reverse(arr, (s+n-1), e);
    reverse(arr, s, e);
}

void printarr (int arr[])
{
    int i =0;
    int n = sizeof(arr);

    printf("\n Len: %d\n",n);
    while (i < n) {
        printf("%d ", arr[i]);
        i++;
    }

    printf("\n");
}

int main (int argc, char **argv)
{
    int i =0, next_pos;
    int n = sizeof(arr);
    //right_rotate(arr);
    //right_rotate_subarray(arr, 2, 5)a

    while (i < n) {
        /*
         * If the numer is positive and it is not in an even position
         */
        if (arr[i] > 0 && (i & 0x1)) {
            /*
             * Get the position of the next element of opposite sign
             */
            next_pos = i+1;

            while (next_pos < n) {
                if (arr[next_pos] < 0)
                   break;
                next_pos++;
            }

            if (next_pos != n) {
                /*
                 * Means we found a negative number
                 */
                right_rotate_subarray(arr, i, next_pos);
            }
        } else if (arr[0] < 0 && !(i & 0x1)) { // Negative number sitting in even position
            /*
             * Get the position of the next opposite
             */
            next_pos = i+1;

            while (next_pos < n) {
                if (arr[next_pos] > 0) {
                    break;
               }
                next_pos++;
            }

            if (next_pos != n) {
                /*
                 * Means we found a positive number
                 */
                right_rotate_subarray(arr, i, next_pos);
            }
        }
        i++;
    }

    printarr(arr);
}
