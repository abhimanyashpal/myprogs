#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// DIAMETER
/*
 * Longest distance between any two nodes in a tree.
 * This may go through the root or not.
 *
 * Formula = max (leftdiameter, rightdiameter, path_thru_root)
 *
 * path thru root = 1 + height(leftsubtree) + heigth(rightsubtree)
 */
typedef int boolean;
#define TRUE 1
#define FALSE 0

typedef struct node_ node_t;

struct node_ {
    int data;
    node_t *left;
    node_t *right;
};

node_t * createNode (int data);

void inorder (node_t *root);
void preorder (node_t *root);
void postorder (node_t *root);

node_t * findMinR (node_t *root);
node_t * findMaxR (node_t *root);
node_t * findMax (node_t *root);
node_t * findMin (node_t *root);

node_t * insert (node_t *root, int data);
node_t * delete (node_t *node, int data);

node_t *
createNode (int data)
{
    node_t *temp = NULL;

    temp = malloc(sizeof(node_t));
    if (!temp)
         return NULL;

    temp->data = data;
    temp->right = temp->left = NULL;

    return temp;
}

void
inorder (node_t *root)
{
    if (!root)
         return;

    inorder(root->left);
    printf ("%d\n",root->data);
    inorder(root->right);
}

void
preorder (node_t *root)
{
    if (!root)
         return;

    printf ("%d\n",root->data);
    preorder(root->left);
    preorder(root->right);
}

void
postorder (node_t *root)
{
    if (!root)
         return;

    postorder(root->left);
    postorder(root->right);
    printf ("%d\n",root->data);
}


node_t *
findMinR (node_t *root)
{
    if (!root)
         return NULL;

    if (root->left == NULL)
        return root;

    return findMinR(root->left);
}

node_t *
findMaxR (node_t *root)
{
    if (!root)
         return NULL;

    if (root->right == NULL)
        return root;

    return findMaxR(root->right);
}

node_t *
findMin (node_t *root)
{
    if (!root)
         return NULL;

    while (root->left != NULL) {
           root = root->left;
    }

    return root;
}

node_t *
findMax (node_t *root)
{
    if (!root)
         return NULL;

    while (root->right != NULL) {
           root = root->right;
    }

    return root;
}

// Recursive insert
node_t *
insert (node_t *root, int data)
{

   if (!root) {
       root = createNode(data);
       if (!root) {
           printf("\n Failed to create node....");
           return NULL;
       }
       root->data = data;
       root->left = root->right = NULL;
       return root;
   }

   if (data < root->data) {
       root->left = insert(root->left, data);
   } else if (data > root->data) {
       root->right = insert(root->right, data);
   } else {
       printf("\n Node already exists !!!!");
   }

   return root;
}

// Iterative insert
void insert_it (node_t *root, int data);

void
insert_it (node_t *root, int data)
{
    if (!root)
         return;

    while (1) {
        while (data < root->data) {
            if (root->left == NULL) {
                root->left = createNode(data);
                return;
            }
            root = root->left;
        }

        while (data >  root->data) {
            if (root->right == NULL) {
                root->right = createNode(data);
                return;
            }
            root = root->right;
        }
     }
}

node_t *
delete (node_t *node, int data)
{
   node_t *temp = NULL;

   if (!node) {
       printf("\n Entry not found");
       return NULL;
   }

   if (data < node->data)
       node->left = delete(node->left, data);
   else if (data > node->data)
       node->right = delete(node->right, data);
   else {
       //Found
       if (node->left && node->right) {
           temp = findMax(node->left);
           if (!temp) {
               printf("\n Failed to delete....");
               return node;
           }

           node->data = temp->data;
           node->left = delete(node->left, temp->data);
       } else {
           temp = node;

           if (!node->left && !node->right) {
               free(temp);
               return NULL;
           }

           if (node->left) {
               node = node->left;
           } else {
               node = node->right;
           }

           free(temp);
       }
   }
   return node;
}

void BST2DLL (node_t *root, node_t **prev, node_t **head);

/*
 * Perform in-order traversal remembering the VISITED nodes
 * in previous. Bottom up approach
 */
void
BST2DLL (node_t *root, node_t **prev, node_t **head)
{
   if (!root)
       return;

   BST2DLL(root->left, prev, head);

   if (*prev == NULL) {
        *head = root;
   } else {
       printf("\n Curr: %d Prev: %d",root->data, (*prev)->data);
       root->left = *prev;
       (*prev)->right = root;
   }

   *prev = root;

   BST2DLL(root->right, prev, head);
}

void printDLL (node_t *root) ;

void
printDLL (node_t *root) 
{
   node_t *node = NULL;
   if (!root)
        return;

   node = root;

   printf("\n Forward\n");

   while (node != NULL) {
      printf("\n %d\n",node->data);
      node = node->right;
   }

   node = root;
   while (node->right != NULL) {
        node = node->right;
   }

   printf("\n Reverse \n");

   while (node != NULL) {
       printf("\n %d \n",node->data);
       node = node->left;
   }
}


void
kth_smallest(node_t *root, int *count, int k, node_t **small);

void
kth_smallest(node_t *root, int *count, int k, node_t **small)
{

   if (!root || !count) {
       return;
   }

   kth_smallest(root->left, count, k, small);


   printf("\n count: %d k: %d curr:%d curr_small:%d",
          *count, k, root->data, (*small ? (*small)->data:0));
   (*count)++;

   if (*small != NULL) {
        printf("\n Smallest element: %d", (*small)->data);
        return;
   }
   if (*count == k) {
        *small = root;
        return;
   }

   kth_smallest(root->right, count, k, small);

}

void
kth_max(node_t *root, int *count, int k, node_t **max);

void
kth_max(node_t *root, int *count, int k, node_t **max)
{

   if (!root || !count) {
       return;
   }

   kth_max(root->right, count, k, max);


   printf("\n count: %d k: %d",*count, k);
   (*count)++;
   if (*count == k) {
        *max= root;
        return;
   }

   kth_max(root->left, count, k, max);

}

int countnodes (node_t *root);
int countnodes (node_t *root)
{
    if (!root)
         return 0;

    printf("\n Data: %d",root->data);
    return (countnodes(root->left) + countnodes(root->right) + 1);
}

// Accumulator has been passed down the stack
void countleft (node_t *root, int *count);
void countleft (node_t *root, int *count)
{

   if (!root)
        return;

   if (root->left) {
       (*count)++;
   }

   countleft(root->left, count);
   countleft(root->right, count);
}

int countleft_no_acc (node_t *root);
int
countleft_no_acc (node_t *root)
{
    int count = 0;

    if (!root)
         return 0;

    if (root->left) {
        count += 1 + countleft_no_acc(root->left);
    }

    count += countleft_no_acc(root->right);

    return count;
}

int countleaf (node_t *root);
int countleaf (node_t *root)
{
   if (!root)
        return 0;

   if (!root->left && !root->right)
        return 1;

#if 0
   if (!root->left && !root->right) {
       (*count)++;
   }

   countleaf(root->left, count);
   countleaf(root->right, count);
#endif

   return countleaf(root->left) + countleaf(root->right);
}

int height (node_t *root);

int
height (node_t *root)
{
    int lh = 0, rh = 0;
    
    if (!root)
         return 0;

    lh = height(root->left);
    rh = height(root->right);

    printf("\n lh:%d rh: %d",lh, rh);

    if (lh > rh) {
        printf("\n lh > rh");
        return (lh + 1);
    } else  {
        printf("\n rh > lh");
        return (rh + 1);
    }
}


/*
 * Trick is to arrive till we are in range
 */
node_t * lca (node_t *root, int a, int b);
node_t *
lca (node_t *root, int a, int b)
{

   if (!root)
        return NULL;

   if (root->data == a || root->data == b)
       return root;

   if ((root->data > a && root->data < b) ||
       (root->data > b && root->data < a)) 
        return root;

   if (root->data > a && root->data > b)
       return lca(root->left, a, b);

   if (root->data < a && root->data < b)
       return lca(root->right, a, b);
}

node_t *
findnode (node_t *root, int data)
{
   node_t *lchild = NULL, *rchild = NULL;

   if (!root) {
        return NULL;
   }

   if (root->data == data)
       return root;

   if (data < root->data)
       lchild = findnode(root->left,data); 

   if (data > root->data)
       rchild = findnode(root->right, data);

   if (lchild)
       return lchild;
   else
       return rchild;
}

boolean isbst (node_t *root, int min, int max);

boolean
isbst (node_t *root, int min, int max)
{
   boolean left = FALSE, right = FALSE;

   if (!root)
       return TRUE;

   if (root->data > min && root->data < max) {
       left = isbst(root->left, min, root->data);
       right = isbst(root->right, root->data, max);

   } else {
       return FALSE;
   }
       if (left && right)
           return TRUE;
       else
           return FALSE;
}

int 
findlevel (node_t *root, int key, int level)
{
  int l =0;

  if (!root)
       return -1;

  if (root->data == key)
      return level;

  l = findlevel(root->left, key, level+1);
  if (l != -1)
      return l;

  return findlevel(root->right, key, level+1);
}

void
print_nodes_at_level(node_t *root, int level)
{

  if (!root)
       return;

  if (level == 0) {
      printf("\n %d",root->data);
  } else {
      print_nodes_at_level(root->left, level-1);
      print_nodes_at_level(root->right, level-1);
  }
}

/*
 * Write a helper API to print nodes at k level
 * below the target node and return.
 *
 * 1.If the node is found on the left-subtree then
 *   check if the root is at a distance of 1 from k, if
 *   yes print it and return "dl+1". Else go to the right
 *   subtree and print nodes below the "k-dl-2" level
 *
 * 2. Symmetric  code for right subtree.
 */
int
k_dist_from_node(node_t *root, int key, int k)
{

  int dl = -1, dr = -1;

  if (!root)
       return -1;

  if (root->data == key) {
      print_nodes_at_level(root,k);
      return 0;
  }

  dl = k_dist_from_node(root->left, key, k);
  if (dl != -1) {
      if ((dl + 1) == k) {
           printf("\n %d",root->data);
      } else {
         print_nodes_at_level(root->right, k-dl-2);
      }

      return 1+dl;
  }
  dr = k_dist_from_node(root->right, key, k);
  if (dr != -1) {
      if ((dr + 1) == k) {
           printf("\n %d",root->data);
      } else {
         print_nodes_at_level(root->left, k-dr-2);
      }

      return 1+dr;
  }
  return -1;
}

/*
 * Keep saving the ancestors in an array, once we hit a leaf 
 * access the kth location from the end of the array, there 
 * len-k-1 from the front.
 *
 * Also use a visited array so that we don't print dups.
 */
void k_dist_from_leaf_util(node_t *node, int path[], int pathlen, int visited[], int k)
{
    if (!node)
         return;

    path[pathlen] = node->data;
    visited[pathlen] = 0;
    pathlen++;

    if (!node->left && !node->right && ((pathlen-k-1) >= 0) && visited[pathlen-k-1] == 0) {
         printf("\n %d",path[pathlen-k-1]);
         visited[pathlen-k-1] = 1;
         return;
    }

    k_dist_from_leaf_util(node->left, path,pathlen,visited,k);
    k_dist_from_leaf_util(node->right, path,pathlen,visited,k);
}

void
k_dist_from_leaf (node_t *node, int k)
{

  int path[100]; int visited[100];
  int pathlen = 0;

  bzero(&visited[0],sizeof(int)*100);

  k_dist_from_leaf_util(node, path,pathlen,visited,k);
}


void
closest_leaf_util(node_t *root, int level, node_t **leaf_ref, int *min_level)
{
   if (!root) {
       *leaf_ref = NULL;
        return;
   }

   if (!root->left && !root->right) {
        if (level < *min_level) {
            *min_level = level;
            *leaf_ref = root;
        }
        return;
   }

   closest_leaf_util(root->left,level+1,leaf_ref,min_level);
   closest_leaf_util(root->right,level+1,leaf_ref,min_level);
}

int
closest_leaf (node_t *root, int key)
{

  node_t *leaf = NULL;
  int ret = -1; 
  int min = INT_MAX;

  if (!root)
       return -1;

  if (root->data == key) {
      closest_leaf_util(root, 0, &leaf, &min);
      if (leaf)
          printf("\n Leaf closest to %d is %d at level %d",root->data, leaf->data, min);
      return 0;
   }

   ret = closest_leaf(root->left, key);
   if (ret == 0)
       return ret;

   return closest_leaf(root->right,key);
}

node_t *root = NULL;

int 
main (int argc, char **argv)
{

  int opt = -1;
  node_t *node = NULL;
  node_t *prev= NULL;
  node_t *head = NULL;
  int elem;
  int count = 0, k =0, a,b;

  if (!root)
      root = insert(NULL,20);

  insert(root,8);
  insert(root,4);
  insert(root,10);
  insert(root,9);
  insert(root,11);
  insert(root,22);

  do {
    printf("\n 1. Insert elem");
    printf("\n 2. Delete elem");
    printf("\n 3. Pre order trav");
    printf("\n 4. In  order trav");
    printf("\n 5. Post order trav");
    printf("\n 6. FindMinR");
    printf("\n 7. FindMaxR");
    printf("\n 8. FindMax");
    printf("\n 9. FindMin");
    printf("\n 10. BST2DLL");
    printf("\n 11. KthSmall");
    printf("\n 12. KthMax");
    printf("\n 13. Count-nodes");
    printf("\n 14. Height");
    printf("\n 15. lca");
    printf("\n 16. find");
    printf("\n 17. count_left_nodes");
    printf("\n 18. count_leaf_nodes");
    printf("\n 19. count_left_no_acc");
    printf("\n 20. Insert iter");
    printf("\n 21. IS BST");
    printf("\n 22. Find level");
    printf("\n 23. Print nodes at a level");
    printf("\n 24. K_dist from a node");
    printf("\n 25. K_dist from a leaf");
    printf("\n 26. Closest leaf to a key");
    printf("\n 27. Exit");

    printf("\n");
    scanf("%d",&opt);

    switch(opt) {
    case 1:
        printf("\n Enter elem:");
        scanf("%d",&elem);
	if (!root)
            root = insert(NULL, elem);
        else
            insert(root,elem);
        break;
    case 2:
        printf("\n Enter elem:");
        scanf("%d",&elem);
        delete(root, elem);
        break;
    case 3:
        preorder(root);
        break;
    case 4:
        inorder(root);
        break;
    case 5:
        postorder(root);
        break;

    case 6:
        node = findMinR(root);
        if (node) {
            printf("\n Min: %d",node->data);
        }
        break;
    case 7:
        node = findMaxR(root);
        if (node) {
            printf("\n Max : %d",node->data);
        }
        break;
    case 8:
        node = findMax(root);
        if (node) {
            printf("\n Max : %d",node->data);
        }
        break;
    case 9:
        node = findMin(root);
        if (node) {
            printf("\n Min: %d",node->data);
        }
        break;
    case 10:
        BST2DLL(root, &prev, &head);
        printDLL(head);
        break;

    case 11:
        printf("\n Enter k:");
        scanf("%d",&k);
        count = 0;

	if (k <= 0)
		printf("\n Invalid input....");
	else {
                node = NULL;
		kth_smallest(root, &count, k, &node);
		if (node)
			printf("\n %d smallest elem: %d\n",k, node->data);
		else
			printf("\n Error \n");
	}
        break;
    case 12:
        printf("\n Enter k:");
        scanf("%d",&k);
        count = 0;

	if (k <= 0)
		printf("\n Invalid input....");
	else {
		kth_max(root, &count, k, &node);
		if (node)
			printf("\n %d max elem: %d\n",k, node->data);
		else
			printf("\n Error \n");
	}
        break;

    case 13:
        printf("Number of nodes: %d",countnodes(root));
        break;

    case 14:
        printf("\nHeight : %d", height(root));
        break;

    case 15:
        printf("\n Enter node-1:");
        scanf("%d",&a);
        printf("\n Enter node-2:");
        scanf("%d",&b);
        node = NULL;
        node = lca(root,a,b);
        if (node)
            printf("\n lca of a:%d and b:%d is %d",a,b, node->data);
        else
            printf("\n No lca found!!!");
        break;

    case 16:
        node = NULL;

        printf("\n Enter data:");
        scanf("%d",&a);

        node = findnode(root,a);
        if (node) {
            printf("\n Found : %d",node->data);
        } else {
            printf("\n Node not found....");
        }
        break;

    case 17:
        a = 0;
        countleft(root, &a);
        printf("\n Left nodes: %d",a);
        break;
    case 18:
        a = 0;
        a = countleaf(root);
        printf("\n leaf nodes: %d",a);
        break;

    case 19:
        a = countleft_no_acc(root);
        printf("\n Left nodes: %d",a);
        break;
    case 20:
        printf("\n Enter data:");
        scanf("%d",&a);
        insert_it(root, a);
        break;
    case 21:
        printf("\n ISBST: %d",isbst(root,INT_MIN,INT_MAX));
        break;

    case 22:
        printf("\n Enter elem: ");
        scanf("%d",&a);
        printf("\n Level of eleme %d is %d",a,findlevel(root,a,0));
        break;
    case 23:
        printf("\n Enter level: ");
        scanf("%d",&a);
        print_nodes_at_level(root,a);
        break;
    case 24:
        printf("\n Enter elem:");
        scanf("%d",&elem);
        printf("\n Enter k: ");
        scanf("%d",&a);
        k_dist_from_node(root,elem,a);
        break;

    case 25:
        printf("\n Enter k: ");
        scanf("%d",&a);
        k_dist_from_leaf(root,a);
        break;
    case 26:
        printf("\n Enter key: ");
        scanf("%d",&a);
        closest_leaf(root,a);
        break;
    case 27:
        break;
    default:
        opt = 27;
        break;
    }
  } while(opt != 27);
}
        
