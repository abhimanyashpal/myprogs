#include <stdio.h>
#include <stdlib.h>

/**
 * Swap every 2 nodes in a linked list
 *
 * Eg :  A --> B --> C --> D  should become

         B --> A --> D --> C

*
*  Eg:   A -->B --> C --> D --> E should become
*
*        B --> A --> D --> C --> E
*/

typedef struct node_ node_t;

struct node_ {
    int     data;
    node_t *next;
};

node_t *head;

node_t *
createnode (int data)
{
    node_t *temp = NULL;

    temp = malloc(sizeof(node_t));
    if (!temp)
        return NULL;

    temp->data = data;
    temp->next = NULL;

    return temp;
}

void
list_add (node_t **head, int data)
{
    node_t *elem = NULL;

    elem = createnode(data);
    if (!elem)
        return;

   elem->next = *head;
 
   *head = elem;
}

void
show_list (node_t *head)
{
    node_t *curr = NULL;

    curr = head;

    while (curr) {
        printf("\n%d",curr->data);
        curr = curr->next;
    }
}

void
move_node (node_t **dst, node_t **src)
{
    //De-couple
    node_t *temp = *src;
    *src = temp->next;

    //Attach to head
    temp->next = *dst;
    *dst = temp;
}

void swap2(node_t **head)
{
    node_t *p1, *p2, *prev,*next;
    node_t *curr;

    if (!head)
        return;

    curr = *head;

    prev = NULL;
    while (curr && curr->next) {
        p1 = curr;
        p2 = curr->next;
        next = p2->next;

        p2->next = p1;
        p1->next = next;

        if (prev) {
            prev->next = p2;
        } else {
            *head = p2;
        }

        prev = p1;
        curr = next;
    }
}

void swap1 (node_t **head)
{
    node_t dummy;
    node_t *tail;
    node_t *curr,*p1,*next;

    dummy.next = NULL;
    tail = &dummy;

    if (!head)
        return;

    curr = *head;

    while (curr && curr->next) {
        next = curr->next->next;

        p1 = curr->next;

        move_node(&tail->next, &p1);
        tail = tail->next;

        move_node(&tail->next, &curr);
        tail = tail->next;

        curr = next;
   }

   tail->next = curr;

   *head = dummy.next;
}

int main (int argc, char **argv)
{
    list_add(&head,6);
    list_add(&head,5);
    list_add(&head,4);
    list_add(&head,3);
    list_add(&head,2);
    list_add(&head,1);

    show_list(head);

    swap1(&head);
    //swap2(&head);

    printf("\n======= AFTER ========");
    show_list(head);
}
