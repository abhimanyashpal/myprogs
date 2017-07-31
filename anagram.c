#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int letters[26];

#define TRUE 1
#define FALSE 0
int is_anagram (const char *str1, const char *str2)
{
    int i = 0,idx;

    if (strlen(str1) != strlen(str2))
        return FALSE;

    printf("\n %s %s\n",str1,str2);

    while (str1[i] != '\0') {
        idx = str1[i] - 'a';

        letters[idx]++;
        i++;
    }

    i =0;
    while (str2[i] != '\0') {
        idx = str2[i] - 'a';

        letters[idx]--;
        if (letters[idx] < 0) 
            return FALSE;
 
        i++;
    }

    return TRUE;
}

int main (int argc, char **argv)
{
    printf("\n IS_ANAGRAM : %d",is_anagram(argv[1],argv[2]));
}
