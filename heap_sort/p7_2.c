#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Heap_ *HeapStruct;
typedef int ElementType;

struct Heap_ {
  int capacity;
  int size;
  ElementType *Elements;
};

HeapStruct CreateHeap(int heap_size);
void Insert(HeapStruct heap, ElementType value);
ElementType DeleteMax(HeapStruct heap);
void PrintHeap(HeapStruct heap);
int IsEmpty(HeapStruct heap);
int IsFull(HeapStruct heap);
void PercolateUp(HeapStruct heap);
void PercolateDown(HeapStruct heap);
void SwapValue(ElementType *a, ElementType *b);
void SortHeap(HeapStruct heap);
ElementType FindMin(HeapStruct heap);

typedef enum {false, true} bool;

int main(int argc, char* argv[]) 
{  
  FILE *pFile;
  char *filename = argv[1];
  char buf[100];
  char *input;
  char *token = " \t\n\r";
  int num;
  if (argc == 1) {
    printf("Usage: ./bst filename\n");
    exit(1);
  }
  HeapStruct heap;
  
  if ( pFile = fopen(filename,"r") )
  {
    while (fgets(buf, sizeof(buf), pFile) != NULL)
    {
      input = strtok(buf, token);

      while ( input != NULL ) {
        if ( !strcmp(input, "n") ) {
          input = strtok(NULL, token);
          num = atoi(input);
          heap = CreateHeap(num);
        } 
        else if ( !strcmp(input, "i") ) {
          input = strtok(NULL, token);
          num = atoi(input); 
          Insert(heap, num);
        }
        else if ( !strcmp(input, "d") ) {
          num = DeleteMax(heap); 
        }
        else if ( !strcmp(input, "p") ) {
          PrintHeap(heap);
        }
        else if ( !strcmp(input, "s") ) {
          SortHeap(heap);
        }
        else printf("%s is invalid input\n", input);
        input = strtok(NULL, token);
      }
    }
    fclose(pFile);
  }
  else {
    printf("NO FILE\n");
  }

  free(heap);

  return 0;
}

HeapStruct CreateHeap(int heap_size) {
  HeapStruct heap = (HeapStruct)malloc(sizeof(struct Heap_));
  heap->capacity = heap_size+1;
  heap->size = 1; // index start at 1
  heap->Elements = (ElementType *)malloc(heap_size*sizeof(ElementType));
  heap->Elements[0] = -1; // unusable space initialization
  return heap;
}

int IsEmpty(HeapStruct heap) {
  return heap->size-1==0?true:false;
}

int IsFull(HeapStruct heap) {
  return heap->size==heap->capacity?true:false;
}

void PercolateUp(HeapStruct heap) {
  // percolating up
  for (int i=heap->size; i>1; i/=2) {
    if ( heap->Elements[i] > heap->Elements[i/2] ) {
      SwapValue(&heap->Elements[i], &heap->Elements[i/2]);
    }
    else continue;
  } 
} // max heap. if min heap, switch (child > parent) to (child < parent)

void PercolateDown(HeapStruct heap) {
  // percolating down
  for (int i=1; i<heap->size; i*=2) {
    if ( heap->Elements[i] < heap->Elements[i*2] && i*2 < heap->size) {
      SwapValue(&heap->Elements[i], &heap->Elements[i*2]);
    }
    else continue;
  } 
} // max heap. if min heap, switch (parent < child) to (parent > child)

void SwapValue(ElementType *a, ElementType *b) {
  ElementType tmp = *a;
  *a = *b;
  *b = tmp;
}

void Insert(HeapStruct heap, ElementType value) {
  if ( IsFull(heap) ) {
    printf("full space\n");
  }
  else {
    if ( heap->size == 1 ) {
      heap->Elements[heap->size++] = value;
    }
    else {
      heap->Elements[heap->size] = value;
      PercolateUp(heap);
      heap->size+=1;
    }
  }
}

ElementType DeleteMax(HeapStruct heap) {
  ElementType deleted_max;
  if ( IsEmpty(heap) ) {
    printf("empty space\n");
  } 
  else {
    deleted_max = heap->Elements[1];
    heap->Elements[1] = heap->Elements[heap->size-1];
    heap->size-=1;
    PercolateDown(heap);
    printf("max element %d has been deleted\n", deleted_max);
  }
  return deleted_max;
}

ElementType FindMin(HeapStruct heap) {
  ElementType min_value = heap->Elements[1];
  int idx = 2;
  while ( idx < heap->size-1 ) {
    if ( min_value > heap->Elements[idx] )
      min_value = heap->Elements[idx];
    idx++;
  }
  return min_value;
}

void SortHeap(HeapStruct heap) {
  ElementType *arr = heap->Elements;
  int var_size = heap->size-1;
  int idx = var_size;

  while ( idx > 1 ) { 
    SwapValue(&arr[1], &arr[idx]);
    // percolating down here
    for (int i=1; i<var_size-1; ) {
      if ((arr[i] < arr[i*2] || arr[i] < arr[i*2+1]) &&
          (i*2 < var_size-1 || i*2+1 < var_size-1)) {

        int *value = arr[i*2]>arr[i*2+1]?&arr[i*2]:&arr[i*2+1];
        int i_next = arr[i*2]>arr[i*2+1]?i*2:i*2+1;
        
        SwapValue(&arr[i], value);
        i = i_next;
      } 
      else {
        i*=2;
        continue;
      }
    }
    var_size--;
    idx--;
    if ( FindMin(heap) == arr[1] ) {
       break;
    }
  }
  printf("sorted array: ");
  for (int i=1; i<heap->size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void PrintHeap(HeapStruct heap) {
  if ( !IsEmpty(heap) ) {
    int level = 1;
    for (int i=1; i < heap->size; i*=2) {
      printf("level %d: ", level++);
      for (int j=i; j < i*2; j++) {
        if ( j < heap->size )
          printf("%d ", heap->Elements[j]);
      }
      printf("\n");   
    }
  }
  else printf("no element\n");
}
