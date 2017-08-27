#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
longest_common_prefix (const char *str1, const char *str2, char *result)
{

    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
         if (str1[i] != str2[i])
             break;

         result[i] = str1[i];
         i++;
    }

    result[i] = '\0';
}

int main (int argc, char **argv)
{
    int len1,len2,min_len,i;
    char *result = NULL;
    char *S[4] = {"leets","leetcode","leet","leets"};
  

    if (argc < 3)
        return 0;

    len1 = strlen(argv[1]);
    len2 = strlen(argv[2]);

    if (len1 < len2) {
      result = malloc((sizeof(char) * len1)+1);
      if (!result)
           return 0;

      result[len1] = '\0';
    } else {
      result = malloc(sizeof(char) * len2 + 1);
      if (!result)
           return 0;

      result[len2] = '\0';
    }

    longest_common_prefix(argv[1],argv[2], result);
    printf("\n LCP: %s",result);
    free(result);

    /******** END OF TEST CODE *******/

    min_len = strlen(S[0]);
    for (i = 1; i < 4; i++) {
         len1 = strlen(S[i]);

         if (len1 < min_len) {
             len1 = min_len;
         }
    }

    printf("\n MIN len string: %d",min_len);
    result = malloc((sizeof(char) * min_len)+1);
    if (!result)
        return 0;

    longest_common_prefix(S[0],S[1],result);

    for (i = 2; i < 4; i++) {
       if (S[i]) {
           longest_common_prefix(result,S[i],result);
       }
    }
    printf("\n LCP: %s",result);
    free(result);

    /***** END OF HORIZONTAL SCANNING ******/
    return 0;
}


