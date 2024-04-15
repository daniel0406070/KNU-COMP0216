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

nptr queue[100];
int front = 0;
int rear = 0;

void enqueue(nptr data){
    queue[rear++] = data;
}

nptr dequeue(){
    nptr temp = queue[front++];
    return temp;
}

void insert(nptr* rootptr,dataType data){
    nptr newnode;
    if(*rootptr == NULL){
        newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        *rootptr = newnode;
    }
    else{
        nptr frontnode = queue[front];
        newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        if(frontnode->left == NULL){
            frontnode->left = newnode;
        }
        else{
            frontnode->right = newnode;
            dequeue();
        }

        
    }
    
    enqueue(newnode);
}

void printnode(nptr* nodeptr){
    printf("%c ",(*nodeptr)->data);
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
    FILE* fp=fopen("input.txt","r");
    if(fp==NULL){
        printf("File open error\n");
        return 0;
    }

    char data;
    while(fscanf(fp,"%c",&data)!=EOF){
        insert(&root,data);
    }

    printf("%-15s: ","Inorder");
    inorder(root);
    printf("\n");

    printf("%-15s: ","Preorder");
    preorder(root);
    printf("\n");

    printf("%-15s: ","Postorder");
    postorder(root);
    printf("\n");


}