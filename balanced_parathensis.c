#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Checks whether an expression has balanced paranthesis,

    Eg:   ([])  --> Balanced
          ([]}  --> Not balanced
          ((([[[{}]]]))) ---> Balanced
 */

typedef struct mystack_ {
    int capacity;
    int top;
    char *arr;
} mystack_t;


mystack_t *S;

mystack_t *
create_stack (int size)
{
    mystack_t *s = NULL;

    s = malloc(sizeof(mystack_t));
    if (!s)
        return NULL;
  
    s->capacity = size;
    s->top = -1;

    s->arr = malloc(sizeof(char) * size);

    if (!s->arr) {
         free(s);
         return NULL;
    }

    bzero(s->arr,sizeof(char)*size);

    return s;
}

void
destroy_stack (mystack_t *s)
{
    if (!s)
        return;

    free(s->arr);
    free(s);
}

int
push (mystack_t *s, char elem)
{
    if (!s || s->top == (s->capacity - 1))
         return -1;

    s->arr[++s->top] = elem;

    return 0;
}

int
pop (mystack_t *s, char *elem)
{
    char t;

    if (!s || s->top == -1 || !elem)
        return -1;

    t = s->arr[s->top];

    *elem = t;

    s->top--;

    return 0;
}

int isempty (mystack_t *s)
{
   return (s->top == -1);
}

int
isbalanced (const char *str)
{
    int i = 0;
    char elem;

    if (!str)
         return 1; //No paranthesis so it is balanced

    while (str[i] != '\0') {
        if ((str[i] == '{') ||
            (str[i] == '(') ||
            (str[i] == '[')) {

             if (push(S,str[i]) < 0) {
               printf("\nFAILED TO PUSH");
               return 0;
             }
        } else {
           switch (str[i]) {
           case ')':
              if (isempty(S))
                return 0;

              pop(S,&elem);
              if (elem != '(')
                  return 0;
              break;
           case '}':
              if (isempty(S))
                return 0;
              pop(S,&elem);
              if (elem != '{')
                  return 0;
              break;
           case ']':
              if (isempty(S))
                return 0;
              pop(S,&elem);
              if (elem != '[')
                  return 0;
              break;
           default:
              break;
           }
       }
       i++;
    }

    return isempty(S);
}

int main (int argc, char **argv)
{

  int ret = 0;

  if (argc < 2)
      return -1;

   S = create_stack(100);
   if (!S)
       return -1;

   ret = isbalanced(argv[1]);

   printf("\nRET: %s",(ret == 0) ? "False":"True");

}

