#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef char dataType;

typedef struct node* nptr;
typedef struct node{
    dataType data;
    nptr left;
    nptr right;
}node;

nptr root = NULL;

void insert(nptr* rootptr,dataType data){
    if(*rootptr == NULL){
        nptr newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        *rootptr = newnode;
    }
    else{
        if((*rootptr)->left == NULL || (*rootptr)->right != NULL){
            insert(&(*rootptr)->left,data);
        }
        else{
            insert(&(*rootptr)->right,data);
        }
    }
}

void printnode(nptr* nodeptr){
    printf("(%p : ",*nodeptr);
    printf("%p ",(*nodeptr)->left);
    printf("%c ",(*nodeptr)->data);
    printf("%p)\n",(*nodeptr)->right);
}

void inorder(nptr root){
    if(root != NULL){
        inorder(root->left);
        printnode(&root);
        inorder(root->right);
    }
}

void preorder(nptr root){
    if(root != NULL){
        printnode(&root);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(nptr root){
    if(root != NULL){
        postorder(root->left);
        postorder(root->right);
        printnode(&root);
    }
}

int main(){
    insert(&root,'A');
    insert(&root,'B');
    insert(&root,'C');
    insert(&root,'D');
    insert(&root,'E');

    printf("Inorder: \n");
    inorder(root);
    printf("Preorder: \n");
    preorder(root);
    printf("Postorder: \n");
    postorder(root);
    return 0;
    
}