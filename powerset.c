#include <stdio.h>

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
