#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Prog to find the longest unique substring in a given string.
 * Basically you should find a contigous string that does not
 * have repeating characters
 */

/*
 * This program will just print all the unique substring , one
 * can extend this to now find the longest
 */


//helper
void substring_helper (const char *str, int start, int end)
{
    int n1 = end-start+2;
    char result[n1];
    int k = 0;

    while (start <= end) {
        result[k++] = str[start++];
    }

    result[k] = '\0';

    printf("\n %s", result);
}

void substring_naive (const char *str, int len)
{
    int i,j;

    for (i = 0; i < len; i++) {
        for (j = i; j < len; j++) {
           substring_helper(str, i, j);
        }
    }
}


int map[26];

void print_sub(char *str, int start, int end)
{
   int n1 = (end-start+2);
   char result[n1];
   int k  = 0;

    while (start <= end) {
        result[k++] = str[start++];
    }

    result[k] = '\0';
   
    printf("\n %s",result);
    
}
int uniq_substr(char *str)
{
    int left = 0, right = 0;
    int idx;

    while (str[right] != '\0') {
        idx = str[right] - 'a';

        if (!map[idx]) {
          map[idx] = (right + 1);
          right++;
          continue;
        }

        //Found a substring
        print_sub(str, left, right-1);
        if (map[idx] > left) {
            left = map[idx];
        } 
         
        map[idx] = (right+1);
        right++;
     }

     //print_sub(str, left, right-1);
     return 0;
}

int main (int argc, char **argv)
{

   char *str = "abcaccbb";

   //substring_naive(str, strlen(str));
   uniq_substr(str);
}
