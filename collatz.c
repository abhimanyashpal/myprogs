#include <stdio.h>


/**
 * Collatz conjecture:
 * Start with any number.
 * If even - then next number is n/2
 * If odd  - then next number is 3n+1
 *
 * We will always end up at 1 , we need
 * to count the number of hops to get to 1.
 */

/*
 * Eg:
 *
 *  5 --> 16 --> 8 --> 4 --> 2 -->1
 *
 *
 * We are 5 hops aways from 1
 *
 * 7 --> 22 --> 11 --> 34 --> 17 --> 52 --> 26 --> 13 --> 40 --> 20 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1
 * 
 * We are 16 hops aways from 1
 */

/*
 * Naive code
 */

int get_next (int n)
{

   if (n & 0x1) {
       return (3*n + 1);
   } else {
       return (n/2);
   }
}

int get_hops (int n)
{
    int hops = -1;
    int count = 1;

    if (n == 1)
        return 0;

    while (get_next(n) != 1) {
        n = get_next(n);
        count++;
    }

    return count;
}

//stubs -- Fill appropriately
static int hash_lkup (int n)
{
    return -1;
}

static void hash_insert (int key, int value)
{
}

static void mystack_push (int key)
{
}

static int mystack_pop (void)
{
   return 0;
}

static int isempty_stack(void)
{
    return 1;
}

/*
 * The above API "get_hops" is not optimized because it recomputes the result
 * from the beginneing for every number.
 * 
 * For eg: if you consider starting with "5" , we have go a hop count say 5 hops
 * Now if we start with say "7" as you can observe in the top most diagram at
 * some point we are crossing "5" for which we had already computed a result
 * earlier , we could have used that result and stopped the loop and returned 
 * from there.
 *
 * Therefore in order to optimized we will always stash the result of our key
 * in a hashtable.
 *
 * We will pre-load the hashtable with the key "1" whose hopcount is 0.
 *
 * So as soon as the user calls the below API , we can first perform a 
 * hash lookup and return the result if already present, otherwise 
 * we can keep moving as per the formula by pushing the intermediate
 * nodes into the stack and searching the hash table till we get either
 * the key "1" or one of the intermediate results.
 *
 * Then we can keep popping our elements from the stack keep saving
 * their results so that it can be used in the future.
 *
 * The below is pseudo code and assumes stack and hash API's are 
 * present.
 */
int get_hops_optimized (int n)
{
    int hops = -1;
    int elem;

    if ( n == 1)
         return 0;

    hops = hash_lkup(n);

    //If the entry was present then we are done
   if (hops != -1) {
      return hops;
   }

   //Otherwise till we get a result keep walking
   while (hops == -1) {
       //push to stack
       mystack_push (n);
   
      //get the next value
      n = get_next(n);

      //re-check the hash table
      hops = hash_lkup(n);
   }

   //So if we consider "5" as the key for the first time , then
   //the above while loop will finish only when we reach 
   // "1" and the other keys viz. 5,16,8,4,2 will all be on
   // the stack.
   // the "hops" value will be 0 because we have terminated at the
   // key of "1"

   //Now empty out our stack.
   //Note the original user passed key will be at the bottom of the stack

   while (!isempty_stack()) {
       elem = mystack_pop();
 
       hops++;
       hash_insert(elem,hops);
   }

   return hops;
    
}

int main (int argc, char **argv)
{
    printf("\n Hop count : %d",get_hops(7));
}
