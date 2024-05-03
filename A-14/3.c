#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500 

typedef struct {   
   int key;
   int item;
} element;


typedef struct node *tptr; 
typedef struct node { 
   element data;
   tptr left, right;
} tnode; 
tptr root = NULL; 

void insert(tptr* node, int k, int theItem); 
element* search(tptr root, int k); 
tptr modifiedSearch(tptr node, int k); 
void inorder(tptr ptr); 

void insert(tptr* node, int k, int theItem) { 
   tptr ptr, temp = modifiedSearch(*node, k); 
   
   if ((temp) || !(*node)) { 
      ptr = malloc(sizeof(*ptr)); 
      ptr->data.key = k; 
      ptr->data.item = theItem; 
      ptr->left = ptr->right = NULL; 
      if (*node) 
         if (k < temp->data.key) temp->left = ptr; 
         else if (k > temp->data.key) temp->right = ptr; 
         else temp= ptr;
      else *node = ptr; 
   }
}

element* search(tptr root, int k) {
   if (!root) return NULL;
   printf("%d => ", root->data.key);
   if (k == root->data.key) return &(root->data);
   if (k < root->data.key)
      return search(root->left, k);
   return search(root->right, k);
}

tptr modifiedSearch(tptr node, int k) { 
   if (!node) 
      return NULL;
   else {
      while (node) { 
         if (!node->left && !node->right) 
            return node;
         if (node->data.key > k){ 
            if (node->left) 
               node = node->left;
            else {
                tptr tempnode;
                tempnode = malloc(sizeof(*node));
                tempnode->data.key = k;
                tempnode->data.item = k;
                tempnode->left = tempnode->right = NULL;
                node->left=tempnode;
                node = node->left;
            }
            
         }  
         else if (node->data.key < k){  
            if (node->right) 
               node = node->right;
            else{
                tptr tempnode;
                tempnode = malloc(sizeof(*node));
                tempnode->data.key = k;
                tempnode->data.item = k;
                tempnode->left = tempnode->right = NULL;
                node->right=tempnode;
                node = node->right;
            }
            
         }
         else 
            return NULL;
      }
   }
}

void inorder(tptr ptr) {
   if (ptr) {
      inorder(ptr->left);
      printf("%3d ", ptr->data.item);
      inorder(ptr->right);
   }
}

int main() {
   int n, item, search_key;
   unsigned int seed; 

   printf("random number generation (1 ~ %d)\n", MAX_SIZE);
   printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
   scanf("%d", &n);
   printf("%s", "seed : ");
   scanf("%u", &seed);

   printf("\ncreating a BST from random numbers\n");
   srand(seed); 
   printf("generating number : ");

   for (int i = 0; i < n; i++) {
      item = rand() % MAX_SIZE + 1; 
      printf("%3d ", item);
      insert(&root, item, item); 
   }
   puts("");


   printf("the key to search : ");
   scanf("%d", &search_key);
   printf("the search process :   ");

   element* result = search(root, search_key);

   if(result) printf("\nthe element is in BST\n");
   else printf("\nthe item not found\n");
   puts("");
   printf("inorder traversal of the BST shows the sorted sequence\n");
   inorder(root);

   return 0;
}
