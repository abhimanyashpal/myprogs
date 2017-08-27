#include <stdio.h>
#include <stdlib.h>

void
printarr (int arr[], int n)
{
  int i;

  printf("\n");
  i = 0;
  while (i < n) {
      printf("%d ",arr[i]);
      i++;
  }
}

void
swap (int *a, int *b)
{
    int temp;

    if (!a || !b)
        return;

    temp = *a;
    *a = *b;
    *b = temp;
}

void
permutations (int i, int arr[], int n)
{
    int j;

    if (i == (n - 1)) {
        printarr(arr, n);
        return;
    }

    for (j = i; j < n; j++) {
       swap(&arr[i], &arr[j]);

       permutations(i+1, arr, n);

       swap(&arr[i], &arr[j]);
    }
}

int main (int argc, char **argv)
{

    int arr[] = {1,2,3};
    permutations(0, arr, 3);
}
