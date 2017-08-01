#include <stdio.h>
#include <stdlib.h>

int arr[] = {1, 2, 1,3,3};

/**
 * Finds the duplicate in O(n) time and constant space
 */
void
find_duplicate (int arr[], int n)
{
    int i = 0, idx = 0;

    while (i < n) {
        idx = abs(arr[i]) - 1;

        //Means we have visited this before and hence duplicate
        if (arr[idx] < 0) {
            printf("\n%d",(idx+1));
        }

        //mark visited by flipping the number
        arr[idx] = -arr[idx];
   
        i++;
    }
}

/**
 * Find missing entry in array with O(n) time and constant space
 */
void
find_missing (int arr[], int n)
{
	int i = 0, idx = 0;

	while (i < n) {
		idx = abs(arr[i]) - 1;

                 //Keep marking
                 if (arr[idx] > 0) {
                     arr[idx] = -arr[idx];
                 }

		i++;
	}

        //Now walk and see which is not marked
        i = 0;
	while (i < n) {
		if (arr[i] > 0) {
			printf("\n Missing: %d",(i+1));
		}
		i++;
	}
}

int main (int argc, char **argv)
{
  int n = sizeof(arr)/sizeof(int);

  //find_duplicate(arr,n);
  find_missing(arr,n);
}
