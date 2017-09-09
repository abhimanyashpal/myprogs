
#include <stdlib.h>
#include <stdio.h>


int a[] =  {10,12,11,94,56,32,34,36,33,35,37};

void helper(int arr[], int start)
{
    int i = 0, j = 0, n = sizeof(a)/sizeof(int);

    printf("\n");
    for (i = start; i < n; i++) {
        for (j = start; j <= i;j++) {
           printf("%d ",arr[j]);
        }
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
}
