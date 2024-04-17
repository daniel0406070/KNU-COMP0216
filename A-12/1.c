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

void infixExpression(nptr* nodeptr){
    nptr node = *nodeptr;
    if(!node) return;

    infixExpression(&node->left);
    printf("%c",node->data);
    infixExpression(&node->right);
}

void prefixExpression(nptr* nodeptr){
    nptr node = *nodeptr;
    if(!node) return;

    printf("%c",node->data);
    prefixExpression(&node->left);
    prefixExpression(&node->right);
}

void postfixExpression(nptr* nodeptr){
    nptr node = *nodeptr;
    if(!node) return;

    postfixExpression(&node->left);
    postfixExpression(&node->right);
    printf("%c",node->data);
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

    
    printf("Infix Expression: ");
    infixExpression(&root);
    printf("\n");

    printf("Prefix Expression: ");
    prefixExpression(&root);
    printf("\n");

    printf("Postfix Expression: ");
    postfixExpression(&root);
    printf("\n");
}