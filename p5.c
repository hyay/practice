#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Circular_Queue *CircularQueue;

struct Circular_Queue {
  int *key;
  int first;
  int rear;
  int qsize;
  int capacity;
};

CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue Q);
int IsFull(CircularQueue Q);
void Dequeue(CircularQueue Q);
void Enqueue(CircularQueue Q, int X);
void PrintFirst(CircularQueue Q);
void PrintRear(CircularQueue Q);
void DeleteQueue(CircularQueue Q);

typedef enum {false, true} bool;

int main() 
{  
  FILE *pFile;
  char buf[100];
  char *input;
  char *token = " \t\n";
  bool is_num = false;
  int num;
  int capacity;
  CircularQueue cq;

  if ( pFile = fopen("expr_input.txt","r") )
  {
    while (fgets(buf, sizeof(buf), pFile) != NULL)
    {
      input = strtok(buf, token);
      while ( input != NULL ) {
        if ( !strcmp(input, "n") ) {
          while ( input != NULL ) {
            is_num = true;
            input = strtok(NULL, token);
            if (input != NULL && is_num == true)
              capacity = atoi(input);
          }
          cq = MakeEmpty(capacity);
        } 
        else if ( !strcmp(input, "e") ) {
          while ( input != NULL ) {
            is_num = true;
            input = strtok(NULL, token);
            if (input != NULL && is_num == true) {
              num = atoi(input);
              Enqueue(cq, num);
            }
          }
        }
        else if ( !strcmp(input, "d") ) {
          Dequeue(cq);
        }
        else if ( !strcmp(input, "f") ) {
          PrintFirst(cq);
        }
        else if ( !strcmp(input, "r") ) {
          PrintRear(cq);
        }
        else printf("invalid input\n");
        is_num = false;
        input = strtok(NULL, token);
      }
    }
    fclose(pFile);
  }
  else
  {
    printf("NO FILE\n");
  }
  DeleteQueue(cq);
  return 0;
}

CircularQueue MakeEmpty(int max) {
  CircularQueue cq = (CircularQueue)malloc(sizeof(struct Circular_Queue));
  cq->key = (int *)malloc(max*sizeof(int));
  cq->first = 0;
  cq->rear = -1;
  cq->qsize = 0;
  cq->capacity = max;
  return cq;
}

int IsEmpty(CircularQueue Q) {
  return Q->qsize==0?true:false;
}

int IsFull(CircularQueue Q) {
  return Q->qsize==Q->capacity?true:false;    
}

void Dequeue(CircularQueue Q) {
  if ( IsEmpty(Q) ) {
    printf("empty space\n");
  } 
  else {
    Q->key[Q->first] = -1;
    Q->first+=1;
    if ( Q->first >= Q->capacity-1 ) {
      Q->first = 0;
    }
    Q->qsize-=1;
  }
}

void Enqueue(CircularQueue Q, int X) {
  if ( IsFull(Q) ) {
    printf("full space\n");
  } 
  else {
    if ( Q->rear >= Q->capacity-1 ) {
      Q->rear = 0;
    }
    else {
      Q->rear+=1;
    }
    Q->key[Q->rear] = X;
    Q->qsize+=1;
  }
}

void PrintFirst(CircularQueue Q) {
  if (IsEmpty(Q)) printf("empty space\n");
  else printf("%d\n", Q->key[Q->first]);
}

void PrintRear(CircularQueue Q) {
  if (IsEmpty(Q)) printf("empty space\n");
  else printf("%d\n", Q->key[Q->rear]);
}

void DeleteQueue(CircularQueue Q) {
  free(Q->key);
  free(Q);
}
