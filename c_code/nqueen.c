#include <stdio.h>
#include <stdlib.h>

int soln[4][4];

int num_queen = 4;

//cols is same as queen-id
int canplace (int row, int cols)
{
    int col,row_idx;

    for (col = 0; col < cols; col++) {
         // Check to see if we can place the queen in the row
         // This will help tell us if there were any previous
         // queens sitting in this row and hence we cannot 
         // insert here.
         if (soln[row][col])
             return 0;
    }

    //We will have to check the diagonals

    //TOP-LEFT
    row_idx = row;
    col = cols;
    while (row_idx >= 0 && col >= 0) {
         if (soln[row_idx][col])
             return 0;

         row_idx--;
         col--; 
    }

    //Bottom-left
    row_idx = row;
    col  = cols;
    while (row_idx < 4 && col >= 0) {
         if (soln[row_idx][col])
             return 0;

         row_idx++;
         col--;
    }

    //Top-right
    row_idx = row;
    col  = cols;
    while (row_idx >= 0 && col < 4) {
         if (soln[row_idx][col])
             return 0;

         row_idx--;
         col++;
    }

    //Bottom-right
    row_idx = row;
    col = cols;
    while (row_idx < 4 && col < 4) {
         if (soln[row_idx][col])
             return 0;

         row_idx++;
         col++;
    }

    return 1;
}

int
solve (int queen)
{
    int row;
    /*
     * Base condition which means all the queens have been placed
     */
    if (queen == num_queen)
        return 1;

    for (row = 0; row < 4; row++) {

         /*
          * Check if we can plaec the queen in the appropriate row.
          *
          * Queen is symbolizes the column id
          */
          if (canplace(row, queen)) {
              soln[row][queen] = 1;
              
              /*
               * Recurse for rest of the queens
               */
               if (solve(queen+1)) {
                   return 1;
               }

              /*
               * This means we found a combination where we cannot place the queen
               */
              soln[row][queen] = 0;
          }
    }

    return 0;
}

int main (int argc, char **argv)
{
   
   //Start with the first queen
    solve(0);

    printf("\n Done.");
}
