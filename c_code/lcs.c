#include <stdio.h>
#include <stdlib.h>

/*
 * Compute the length of the longest common subsequence
 *
 * Eg s1 = "abcd" s2 = "acde" , length = 3 since "acd" is a 
 * subsequence
 */



/*
 * Recursive API
 */
int lcs_r (char *s1, char *s2)
{
    int l1 = 0, l2 = 0;

    if (*s1 == '\0' || *s2 == '\0')
         return 0;

    if (*s1 == *s2) {
        /*
         * Move bothe forward
         */
         return (1 + lcs_r(s1+1, s2+1));
    }

    l1 = lcs_r(s1+1,s2);
    l2 = lcs_r(s1, s2+1);

    /*
     * Return max
     */
   if (l1 > l2)
       return l1;
   else
       return l2;
}

int main (int argc, char **argv)
{
    int len = 0;

    len = lcs_r("abcd","acde");

    printf("\n %u",len);
}
