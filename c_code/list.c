#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node_t;

struct node_ {
    int data;
    node_t *next;
};

int
count (node_t *head)
{

  int c = 0;
  node_t *curr = head;

  if (!curr)
      return 0;

  while (curr != NULL) {
      c++;
      curr = curr->next;
  }

  return c;
}

void printlist (node_t *head)
{

  node_t *curr = head;

  if (!curr) {
       printf("\n Empty....");
       return;
  }

  printf("\n Dumping list......");
  while (curr != NULL) {
      printf("\n %d",curr->data);
      curr = curr->next;
  }

  printf("\n Done");
}

int
getnth (node_t **head, int idx)
{
   node_t *prev = NULL;
   node_t *curr = *head;
   int count = 0;

   if (idx < 0) {
       printf("\n Invalid index");
       return -1;
   }

   if (!curr) {
       printf("\n Empty...");
       return -1;
   }

   while (curr) {
       if (count == idx) {
           return curr->data;
       }
       count++;
       curr = curr->next;
   }

   //Not found
   printf("\n No data found");
   return -1;
}

//Inserts at the beginning or within a list
void
insert_nth (node_t **head, int data, int idx)
{

  node_t *node = NULL;
  node_t *prev= NULL, *curr = NULL;
  int c = 0;

  c = count(*head);

  if (idx < 0 || idx > c-1) {
      printf("\n Invalid index...");
      return;
  }

  if (idx == 0) {
      node = malloc(sizeof(node_t));
      node->data = data;
      node->next = *head;
      *head = node;
      return;
  }

  prev = NULL;
  curr = *head;

  while (idx != 0 && curr) {
      prev = curr;
      curr = curr->next;
      idx--;
  }

  node = malloc(sizeof(node_t));
  node->data = data;
  
  prev->next = node;
  node->next = curr;

  return;
}

void push (node_t **head, int data)
{

  node_t *temp = NULL;

  temp = malloc(sizeof(node_t));
  if (!temp)
      return;
 
  temp->data = data;
  temp->next = NULL;

  if (!(*head)) {
      *head = temp;
       return;
  }

  temp->next = *head;
  *head = temp;
}

void movenode (node_t **dst, node_t **src)
{
  node_t *temp = NULL;

  if (!(*src)) {
       printf("\n Source cannot be empty...\n");
       return;
  }

  temp = *src;
  *src = temp->next;
  temp->next = NULL;

  temp->next = *dst;
  *dst = temp;
}

void
sort_insert (node_t **head, int data)
{

  node_t *node = NULL;
  node_t *prev, *curr;

  node = malloc(sizeof(node));
  node->data = data;
  node->next = NULL;

  //Empty list
  if (!(*head)) {
      *head = node;
       return;
  }

  curr = *head;

  //Beginning of the list
  if (node->data < curr->data) {
      node->next = curr;
      *head = node;
       return;
  }

  //Single node
  if (curr->next == NULL) {
       curr->next = node;
       return;
   }

   prev = curr;
   curr = curr->next;
   do {

        if (node->data > prev->data && node->data < curr->data) {
            prev->next = node;
            node->next = curr;
            return;
        }

        prev = curr;
        curr = curr->next;
   } while (curr != NULL);

   //inserting greatest node
   prev->next = node;
}



// Return the data in the node
int pop (node_t **head)
{
  node_t *temp = *head;
  int data;

  if (!temp) {
       printf("\n Empty list...");
       return -1;
  }

  data = temp->data;

  *head = temp->next;

  temp->next = NULL;
  free(temp);

  return data;
}

void
sortlist (node_t **head)
{

  node_t *prev,*curr;
  int c,temp;

  if (!(*head) || (*head)->next == NULL)
      return;

  c = count(*head);

  while (c != 0) {
     prev = *head;
     curr = prev->next;

     while (curr) {
        if (prev->data > curr->data) {
            temp = prev->data;
            prev->data = curr->data;
            curr->data = temp;
        }
        prev = curr;
        curr = curr->next;
     }
     c--;
   }
}

void
append (node_t **head_a, node_t **head_b)
{

  node_t *curr = NULL;

  if (!(*head_a)) {
      *head_a = *head_b;
      *head_b = NULL;
      return;
  }

  curr = *head_a;

  while (curr->next) {
       curr = curr->next;
  }

  curr->next = *head_b;
  *head_b = NULL;
}

//list needs to be sorted
void
removedup (node_t **head)
{

  node_t *prev, *curr,*temp;

  if (!(*head))
      return;

  if ((*head)->next == NULL)
      return;

  prev = *head;
  curr = prev->next;

  while (curr) {
      if (prev->data == curr->data) {
          temp = curr;
          prev->next = curr->next;
          curr = curr->next;
          free(temp);
          continue;
       }

       prev = curr;
       curr = curr->next;
  }
}


void alternatesplit (node_t **head)
{
  node_t *lista=NULL,*listb=NULL,*curr=NULL;
  int c = count(*head);
  int even = 1;

  if (c == 0 || c == 1) {
      printf("\n %s",c ? "Empty":"Too few elems");
      return;
  }

  curr = *head;

  while (curr) {
     if (even) {
       movenode(&lista,&curr);
     } else {
       movenode(&listb,&curr);
     }
     even = !even;
  }

  printf("\n Printing list-a");
  printlist(lista);
  printf("\n Printing list-b");
  printlist(listb);

}

void frontbacksplit (node_t **head, 
                     node_t **list_a, 
                     node_t **list_b)
{

  node_t *lista = NULL; node_t *listb = NULL;

  node_t *p1,*p2;

  if (!(*head))
       return;

  p1 = *head;

  if (p1->next == NULL) {
      printf("\n Single elem, nothing to split");
      return;
  }

  if (p1->next->next == NULL) {
      // Only 2 nodes
      lista = p1;
      listb = p1->next;
      p1->next = NULL;

      *list_a = lista;
      *list_b = listb;
 
      return;
   }

   lista = p1;

   p2 = p1;

   while (p2 && p2->next) {
      p2 = p2->next->next;
      p1 = p1->next;
   }

   listb = p1->next;
   p1->next = NULL;

   *list_a = lista;
   *list_b = listb;
}

void listrev_r (node_t **head, node_t *prev, node_t *curr)
{

   if (!(*head))
       return;

   if (curr->next == NULL) {
       curr->next = prev;
       *head = curr;
        return;
   }

   listrev_r(head,curr,curr->next);
   curr->next = prev;
}

void listrev (node_t **head)
{

  node_t *curr,*prev,*next;

  if (!(*head))
       return;

  prev = NULL;
  curr = *head;

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  *head = prev;
}

void printbackward (node_t *head)
{

  node_t *curr,*prev,*next;

  if (!head)
       return;

  prev = NULL;
  curr = head;

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  curr = prev;
  prev = NULL;

  while (curr) {
     printf("\n %d",curr->data);
     next = curr->next;
     curr->next = prev;
     prev = curr;
     curr = next;
  }
}

node_t *
merge_list (node_t *lista, node_t *listb)
{
  node_t dummy;
  node_t *tail = &dummy;
  
  dummy.next= NULL;

  while (1) {
     if (lista == NULL) {
         tail->next = listb;
         break;
     } else if (listb == NULL) {
         tail->next = lista;
         break;
     } else {
         if (lista->data <= listb->data) {
             movenode(&tail->next,&lista);
         } else {
             movenode(&tail->next,&listb);
         }
         tail = tail->next;
     }
  }
  return dummy.next;
}

node_t *
merge_list_r (node_t *lista, node_t *listb)
{
    node_t *result = NULL;

    if (lista == NULL) {
        return listb;
    } else if (listb == NULL) {
        return lista;
    } else {
        if (lista->data <= listb->data) {
            result = lista;
            result->next = merge_list_r(lista->next, listb);
        } else {
            result = listb;
            result->next = merge_list_r(lista, listb->next);
        }
        return result;
    }
}

node_t *
shufflemerge_r (node_t *lista, node_t *listb)
{

  node_t *recur, *result;

  if (!lista)
       return listb;
  else if (!listb) {
       return lista;
  } else {
      recur = shufflemerge_r(lista->next, listb->next);

      result = lista;
      lista->next = listb;
      listb->next = recur;
      return result;
  }
}
      
node_t *
shufflemerge (node_t *lista, node_t *listb)
{

  int flip = 1;
  node_t *dst = NULL;

  node_t *lista_c = lista;
  node_t *listb_c = listb;

  while (lista_c && listb_c) {
       if (flip) {
           movenode(&dst,&lista_c);
       } else{
           movenode(&dst,&listb_c);
       }
       flip = !flip;
  }

  while (lista_c) {
      movenode(&dst,&lista_c);
  }
  while (listb_c) {
      movenode(&dst,&listb_c);
  }

  return dst;
}

void
merge_sort (node_t **head)
{

  node_t *a = NULL, *b = NULL;

  if (!(*head) || (*head)->next == NULL)
       return;

  frontbacksplit(head,&a,&b);

  merge_sort(&a);
  merge_sort(&b);
  *head = merge_list(a,b);
}

//Finds out the common nodes in a list
node_t * 
	SortedIntersect(node_t* a, node_t* b) {
		node_t dummy;
		node_t* tail = &dummy;
		dummy.next = NULL;

		// Once one or the other list runs out -- we're done
		while (a!=NULL && b!=NULL) {
			if (a->data == b->data) {
				push((&tail->next), a->data);
				tail = tail->next;
				a = a->next;
				b = b->next;
			}
			else if (a->data < b->data) { // advance the smaller list
				a = a->next;
			}
			else {
				b = b->next;
			}
		}
		return(dummy.next);
	}


	int main (int argc, char **argv)
	{

	  node_t *head = NULL;
	  node_t *head_b = NULL;
	  node_t *shuf = NULL;
	  node_t *list_a = NULL; node_t *list_b = NULL;
	  int idx = 0, data;

	  push(&head,5);
	  push(&head,3);
	  push(&head,1);
	  
	  push(&head_b,5);
	  push(&head_b,4);
	  push(&head_b,3);

	  printf("\n Count: %d",count(head));
	  printlist(head);

	#if 0
	  printf("\n Element %d",pop(&head));
	  printlist(head);
	  printf("\n Count: %d",count(head));
	  
	  printf("\n Element %d",pop(&head));
	  printf("\n Element %d",pop(&head));
	  printf("\n Element %d",pop(&head));
	  printlist(head);
	  printf("\n Count: %d",count(head));
	#endif

	  //printf("\n Enter idx:");
	  //scanf("%d",&idx);

	  //data = getnth(&head,idx);
	  //printf("\n Data: %d",data);

	  //insert_nth(&head,10,7);
	  //printlist(head);

	  //sort_insert(&head,8);

	  //sortlist(&head);
	  //printlist(head);
	  
	  //push(&head_b,6);
	  //push(&head_b,2);
	  //push(&head_b,3);
	  //push(&head_b,4);
	  
	  //printlist(head_b);

	  //append(&head, &head_b);

	  printf("\n Orig....\n");
	  printlist(head);

	  //frontbacksplit(&head,&list_a,&list_b);

	  //removedup(&head);

	  printf("\n Printing list-a");
	  printlist(list_a);
	  printf("\n Printing list-b");
	  printlist(list_b);

	  //movenode(&head,&head_b);
	  //movenode(&head,&head_b);
	  //movenode(&head,&head_b);

	  //alternatesplit(&head);
	  //listrev(&head);

	  //printf("\n Back....");
	  //printbackward(head);

	  //printf("\n Orig...");
	  //printlist(head);

	  //listrev_r(&head,NULL,head);
	  //printlist(head);

	  //shuf = shufflemerge_r(list_a,list_b);
	  //printf("\n Shuffled list.....");
	  //printlist(shuf);

	  //sortlist(&list_a);
	  //sortlist(&list_b);
	  shuf = merge_list(list_a,list_b);
	  printlist(shuf);

	  //merge_sort(&list_a);
	  //printlist(list_a);

	  //printlist(head);
	  printf("\n=========\n");
	  //printlist(head_b);
	  //shuf = SortedIntersect(head,head_b);
  //printlist(shuf);

  //printlist(head);
  //printf("\n=========\n");
  //printlist(head_b);

}
