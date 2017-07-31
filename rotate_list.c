#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct node_ node_t;

struct node_ {
	int data;
	node_t *next;
};

node_t *head = NULL;

node_t * createnode (int data)
{
	node_t *node = NULL;

	node = malloc(sizeof(node_t));
	if (!node)
		return NULL;

	bzero(node,sizeof(node_t));

	node->data = data;
	node->next = NULL;

	return node;
}

void insert (node_t **head, int data)
{
	node_t *node = NULL;

	node = createnode(data);
	if (!node)
		return;


	node->next = *head;

	*head = node;

	return;
}

void printlist (node_t *head)
{
	node_t *node = head;

	while(node) {
		printf("\n %d",node->data);
		node = node->next;
	}
}

int count_nodes (node_t *head)
{
	node_t *node = head;
	int count = 0;

	if (!node)
		return 0;

	while (node) {
		count++;
		node = node->next;
	}

	return count;
}

void rot_list (node_t **head, int k)
{
	node_t *lista = NULL;
	node_t *listb = NULL;
	node_t *temp = NULL;
	int bal = 0;

	int count = 0;

	count = count_nodes(*head);

	k = k % count;

	if (!k)
            return;


	bal = count - k;

	printf("\n Count: %d Balance: %d",count, bal);

	lista = *head;
	while (bal > 1 && lista) {
		lista = lista->next;
		bal--;
	}

	listb = lista->next;

	lista->next = NULL;

	printf("\n Listb....");
	printlist(listb);
	printf("\n Lista....");
	printlist(*head);

	printf("\n Rotating");
	temp = *head;
	*head = listb;
	while (listb->next) {
		listb = listb->next;
	}

	listb->next = temp;


	printlist(*head);
}

int main (int argc, char **argv)
{
	insert(&head, 1);
	insert(&head, 2);
	insert(&head, 3);
	insert(&head, 4);
	insert(&head, 5);

	printlist(head);

	rot_list(&head, 10001);
}
