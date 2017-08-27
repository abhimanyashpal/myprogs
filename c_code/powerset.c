#include <stdio.h>

/*
 * Powerset of a set S is all the subsets of the complete S
 */

/*
 * In the below example the output should be
 *  [1] , [1 2] , [1 2 3], [2] , [2 3] , etc
 */
int arr[] = {1,2,3};

int res[3];
int idx;

void printarr(int res[])
{
    int i = 0;

    for (i =0 ; i < idx; i++) {
         printf("%d ",res[i]);
    }

    printf("\n");
}

int powerset(void)
{
    int i; int pow_set_size = 1 << 3;
    int set_size = 3;
    int j;

    /*
     * Represent the various combinations as a bitmap and test
     * the individual array indice in the bitmap.
     *
     * If the bit is set then the array element can be added 
     * to the set
     *
     * In the example array we have 3 values and hence 2^3 different
     * combinations.
     *
     * We run from 0-7 and test each of the array indice in the
     * values from 0-7
     */
    for (i =0 ; i < pow_set_size; i++) {
        for (j =0 ; j < set_size; j++) {
            if (i & (1 << j)) {
              printf("%d ",arr[j]);
            }
        }
        printf("\n");
    }
    return 0;
}

int main (int argc, char **argv)
{

    powerset();
   
}
