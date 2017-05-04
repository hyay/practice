#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_ Tree;
typedef struct Tree_ Node;

struct Tree_ {
  int value;
  Tree *left;
  Tree *right;
};

Tree *InsertNode(Tree *root, int key);
Tree *DeleteNode(Tree *root, int key);
Tree *FindNode(Tree *root, int key);
Node *FindMinNode(Tree *root);
Node *FindMaxNode(Tree *root);
void PrintInorder(Tree *root);
void PrintPreorder(Tree *root);
void PrintPostorder(Tree *root);

typedef enum {false, true} bool;


int main(int argc, char* argv[]) 
{  
  FILE *pFile;
  char *filename = argv[1];
  char buf[100];
  char *input;
  char *token = " \t\n\r";
  int num;
  Tree *bst = NULL;
  if (argc == 1) {
    printf("Usage: ./bst filename\n");
    exit(1);
  }
  
  if ( pFile = fopen(filename,"r") )
  {
    while (fgets(buf, sizeof(buf), pFile) != NULL)
    {
      input = strtok(buf, token);

      while ( input != NULL ) {
        if ( !strcmp(input, "i") ) {
          input = strtok(NULL, token);
          num = atoi(input);
          if ( bst == NULL ) printf("empty tree\n");
          bst = InsertNode(bst, num);
        } 
        else if ( !strcmp(input, "d") ) {
          input = strtok(NULL, token);
          num = atoi(input); 
          bst = DeleteNode(bst, num);
        }
        else if ( !strcmp(input, "f") ) {
          input = strtok(NULL, token);
          num = atoi(input);
          if ( FindNode(bst, num) == NULL ) {
            printf("%d is not in the tree\n", num);
          }
          else { 
            printf("%d is in the tree\n", num);
          }
        }
        else if ( !strcmp(input, "pi") ) {
          PrintInorder(bst);
          printf("\n");
        }
        else if ( !strcmp(input, "pr") ) {
          PrintPreorder(bst);
          printf("\n");
        }
        else if ( !strcmp(input, "po") ) {
          PrintPostorder(bst);
          printf("\n");
        }
        else {
          if ( !strcmp(input, "n") ) continue;
          else printf("%s is invalid input\n", input);
        }
        input = strtok(NULL, token);
      }
    }
    fclose(pFile);
  }
  else {
    printf("NO FILE\n");
  }

  free(bst);

  return 0;
}

Tree *InsertNode(Tree *root, int key) {
  if ( root == NULL ) {
    Tree *bst = (Tree *)malloc(sizeof(struct Tree_));
    bst->value = key;
    bst->left = NULL;
    bst->right = NULL;
    root = bst;
    return root;
  }
  else {
    if ( root->value > key ) { 
      root->left = InsertNode(root->left, key);
    } 
    else if ( root->value < key ) { 
      root->right = InsertNode(root->right, key);
    }
    else {
      printf("%d already exists in the tree\n", key);
    }
    return root;
  }
}

Tree *DeleteNode(Tree *root, int key) {
  Node *tmp = NULL;

  if ( root != NULL ) {
    if ( root->value > key ) {
      root->left = DeleteNode(root->left, key);
    }
    else if ( root->value < key ) {
      root->right = DeleteNode(root->right, key);
    }
    else if ( root->left && root->right ) { // 2 child
      tmp = FindMinNode(root->right); // find min node from right subtree
      root->value = tmp->value;
      root->right = DeleteNode(root->right, root->value);
    }
    else { // 0 or 1 child
      tmp = root;
      if ( root->left == NULL ) {
        root = root->right;
      }
      else if ( root->right == NULL ) {
        root = root->left;
      }
      free(tmp);
    }
    return root;
  }
  else { 
    printf("element not found\n"); 
    return tmp;
  }
}

Tree *FindNode(Tree *root, int key) {
  // find key in the tree
  Tree *tmp = NULL;
  
  if ( root != NULL ) {
    if ( root->value == key ) {
      return root;
    }
    else if ( root->value > key ) {
      tmp = FindNode(root->left, key);
      return tmp;
    }
    else if ( root->value < key ) {
      tmp = FindNode(root->right, key);
      return tmp;
    }
  }
  else return tmp;
}
/*  // recursive implementation
Node *FindMinNode(Tree *root) {
  Node *node = NULL;
  
  if ( root != NULL ) { 
    if ( root->left != NULL ) {   
      node = FindMinNode(root->left);     
    }
    else { 
      node = root;
      return node;
    }
  }
  else return node;
}
*/
// nonrecursive implementation
Node *FindMinNode(Tree *root) {
  if ( root != NULL ) {
    while ( root->left != NULL ) {
      root = root->left;
    }
    return root;
  }
  else return NULL; 
}

Node *FindMaxNode(Tree *root) {
  if ( root != NULL ) {
    while ( root->right != NULL ) {
      root = root->right;
    }
    return root;
  }
  else return NULL;
}

void PrintInorder(Tree *root) {
  // left -> root -> right
  if ( root != NULL ) {
    PrintInorder(root->left);
    printf("%d ", root->value);
    PrintInorder(root->right);
  }
}

void PrintPreorder(Tree *root) {
  // root -> left -> right
  if ( root != NULL ) {
    printf("%d ", root->value);
    PrintPreorder(root->left);
    PrintPreorder(root->right);
  }
}

void PrintPostorder(Tree *root){
  // left -> right -> root
  if ( root != NULL ) {
    PrintPostorder(root->left);
    PrintPostorder(root->right);
    printf("%d ", root->value);
  }
}
