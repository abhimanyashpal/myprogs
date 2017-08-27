#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef enum {
    MIN_HEAP = 1,
    MAX_HEAP = 2
}heap_type;

typedef struct heap_ {
    int       *arr;
    int       capacity;
    int       count;
    heap_type type;
} heap_t;

int arr[10] = {6,5,4,3,2,1};

static heap_t *
CreateHeap (int capacity, heap_type type)
{

  heap_t *heap = NULL;

  if (type < MIN_HEAP || type > MAX_HEAP)
      return NULL;

  heap = malloc(sizeof(heap_t));
  if (!heap)
       return NULL;

  bzero(heap, sizeof(heap_t));

  heap->capacity = capacity;

  heap->arr = malloc(sizeof(int) * capacity);
  if (!heap->arr) {
       free(heap);
       return NULL;
  }

  bzero(heap->arr, (sizeof(int)*capacity));

  heap->type = type;

  return heap;
}

static int
GetParentIdx (heap_t *heap, int i)
{

  if (!heap || i <= 0 || i >= heap->count)
       return -1;

  return ((i - 1)/2);
}

static int
GetLeft (heap_t *heap, int i)
{

   int left = (2*i + 1);
   if (!heap || left >= heap->count)
        return -1;

   return left;
}

static int
GetRight (heap_t *heap, int i)
{
   int right = (2*i+2);

   if (!heap || right >= heap->count)
        return -1;

   return right;
}

static void
percolate_down (heap_t *heap, int i)
{

   int l,r,max,min, temp;

   l = GetLeft(heap, i);
   r = GetRight(heap,i);

   if (heap->type == MAX_HEAP) {
	   if (l != -1 && heap->arr[l] > heap->arr[i])
		   max = l;
	   else
		   max = i;

	   if (r != -1 && heap->arr[r] > heap->arr[max])
		   max = r;

	   if (max != i) {
		   // Swap
		   temp = heap->arr[i];
		   heap->arr[i] = heap->arr[max];
		   heap->arr[max] = temp;

		   percolate_down(heap, max);
	   }
   } else {
      if (l != -1 && heap->arr[l] < heap->arr[i])
           min = l;
      else
           min = i;

      if (r != -1 && heap->arr[r] < heap->arr[min])
           min = r;
      
      if (min != i) {
	// Swap
	temp = heap->arr[i];
	heap->arr[i] = heap->arr[min];
	heap->arr[min] = temp;
        percolate_down(heap, min);
      }
  }
}

static void
printelem (heap_t *heap)
{

  int i;

  if (!heap)
       return;

  for (i = 0; i < heap->count; i++) {
       printf("\n %d", heap->arr[i]);
  }
}

static int
deleteMax (heap_t *heap)
{
   int max;

   if (!heap)
        return -1;

   max = heap->arr[0];
   printf("\n Dequeing element %d",max);

   heap->arr[0] = heap->arr[heap->count - 1];
   heap->count--;

   percolate_down(heap,0);

   return max;
}

static int
findkthlargest(heap_t *heap,int k)
{
   int max;

   if (!heap)
        return -1;

   while (k > 0) {
       max = deleteMax(heap);
       k--;
   }

   return max;
}

static int
delete (heap_t *heap, int i)
{
   int max;

   if (!heap)
        return -1;

   max = heap->arr[i];
   printf("\n Dequeing element %d",max);

   heap->arr[i] = heap->arr[heap->count - 1];
   heap->count--;

   percolate_down(heap,i);

   return max;
}

static int
buildheap (heap_t *heap, int arr[], int count)
{

   int i;

   if (!heap)
        return -1;

   if (count >= heap->capacity) {
       // Need to resize, for now fail
       return -1;
   }

   heap->count = count;

   memcpy(&heap->arr[0], &arr[0], (count * sizeof(int)));

   for (i = 0; i < heap->count ; i++) {
        printf("\nIdx:%d parent:%d left:%d right:%d Data:%d",
                i,
                GetParentIdx(heap,i),
                GetLeft(heap,i),
                GetRight(heap,i),
                heap->arr[i]);
   }

   for (i = ((count - 1)/2); i >= 0; i--)
        percolate_down(heap, i);

   printf("\n After heapifying........\n");
   for (i = 0; i < heap->count ; i++) {
        printf("\nIdx:%d parent:%d left:%d right:%d Data:%d",
                i,
                GetParentIdx(heap,i),
                GetLeft(heap,i),
                GetRight(heap,i),
                heap->arr[i]);
   }

   return 0;
}

static void
insert (heap_t *heap, int data)
{
   int i = 0;

   if (!heap)
        return;

   heap->count++;

   i = heap->count - 1;

   if (heap->type == MAX_HEAP) {
	   while (i > 0 && data > heap->arr[(i-1)/2]) {
		   heap->arr[i] = heap->arr[(i-1)/2];

		   i = (i-1)/2;
	   }
   } else {
	   while (i > 0 && data < heap->arr[(i-1)/2]) {
		   heap->arr[i] = heap->arr[(i-1)/2];
		   i = (i-1)/2;
	   }
   }

   heap->arr[i] = data;
}

static void
myheapsort (heap_t *heap)
{

  int i, old_size, temp, brk = 0;

  old_size = heap->count;

  for (i = (old_size - 1); i > 0; i--) {

       temp = heap->arr[0];
       heap->arr[0] = heap->arr[heap->count - 1];
       heap->arr[heap->count - 1] = temp;

       heap->count--;

       percolate_down(heap, 0);
  }
  heap->count = old_size;

}

int main (int argc, char **argv)
{

  heap_t *heap = CreateHeap(20,MIN_HEAP);

  if (heap) {
      printf("\n Created a %s heap with capacity %d",
               (heap->type == MAX_HEAP) ? "Max":"Min",
                heap->capacity);
  } else {
      printf("\n Failed to create a heap");
  }

  //buildheap(heap,arr, 6);

  //deleteMax(heap);

  insert(heap,10);
  insert(heap,14);
  insert(heap,11);
  insert(heap,6);
  insert(heap,7);
  //printelem(heap);

  myheapsort(heap);
  printelem(heap);

  //delete(heap,1);
  //printelem(heap);

  //findkthlargest(heap,5);

}
