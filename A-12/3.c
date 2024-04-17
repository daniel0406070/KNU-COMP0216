#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* operators = "+-*/%%";

typedef struct node* nptr;
typedef struct node{
    char data;
    nptr left;
    nptr right;
}node;

nptr root = NULL;

nptr stack[100];
int top = -1;

void push(nptr data){
    stack[++top] = data;
}

nptr pop(){
    if(top == -1) return NULL;
    return stack[top--];
}


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


void insert(nptr* rootptr, char data){
    if(strchr(operators,data)){
        nptr newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->right = pop();
        newnode->left = pop();
        push(newnode);
    }
    else{
        nptr newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        push(newnode);
    }
}

void prefixExpression(nptr* nodeptr){
    nptr node = *nodeptr;
    top = -1;
    
    while(1){
        for(;node;node=node->left){
            push(node);
            if(node) printf("%c",node->data);
        }

        node = pop();
        if(!node) break;

        node = node->right;
    }
}

void postfixExpression(nptr* nodeptr){
    nptr node = *nodeptr;
    top = -1;
    char str[100];
    int idx = 0;
    
    while(1){
        for(;node;node=node->right){
            push(node);
            if(node) str[idx++] = node->data;
        }

        node = pop();
        if(!node) break;

        node = node->left;
    }

    for(int i=idx-1; i>=0; i--){
        printf("%c",str[i]);
    }
}



int main(){
    FILE* fp = fopen("input.txt","r");
    char str[90];
    printf("the length of input string should be less than 80\n");
    
    fscanf(fp,"%s",str);
    printf("input string: %s\n",str);

    printf("creating binary tree\n");
    int len = strlen(str);
    for(int i=0; i<len; i++){
        insert(&root,str[i]);
    }
    root = pop();
    printf("\n");

    
    printf("Prefix Expression: ");
    prefixExpression(&root);
    printf("\n");

    printf("Postfix Expression: ");
    postfixExpression(&root);
    printf("\n");
}



