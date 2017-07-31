#include <stdio.h>

#define NUM_ITEMS 4 
#define  MAX_WT 7

int wt[NUM_ITEMS] = {1,3,4,5};
int val[NUM_ITEMS] = {1,4,5,7};

int soln[NUM_ITEMS+1][MAX_WT +1];

#define my_max(a,b)  ((a) > (b)) ? (a) : (b)

int main (int argc, char **argv)
{
	int row, col, remaining_wt;

	//Item-0 means no items present in shop.
	// Therefor irrespective of wt the soln
	// value will be 0.
	for (col = 0 ; col < (MAX_WT+1); col++) {
		soln[0][col]  = 0;
	}

	//If we don't have a knapsack then irrespective
	// of the number of items we can't pick anything.
	for (row = 0; row < (NUM_ITEMS + 1); row++) {
		soln[row][0] = 0;
	}

	for (row = 1; row < (NUM_ITEMS+1); row++) {
		for (col = 1; col < (MAX_WT + 1); col++) {
			if (wt[row-1] <= col) {
				/*
				 * We can pick this item
				 * Formula = max (item_Wt + remaining wt or if the item is not selected)
				 */
				remaining_wt = col - wt[row-1];
				soln[row][col] = my_max((val[row - 1] + soln[row-1][remaining_wt]), soln[row-1][col]);
			} else {
				/*
				 * Pick same as previous item
				 */
				soln[row][col] = soln[row-1][col]; 
			}
		}
	}

	for (row = 0; row < (NUM_ITEMS+1); row++) {
		for (col = 0; col < (MAX_WT + 1); col++) {
			printf("%d ",soln[row][col]);
		}
		printf("\n");
	}

        printf("\n MAXIMUM VALUE: %d\n", soln[NUM_ITEMS][MAX_WT]);
}
