#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char var[3] = {0,};
typedef struct node* nptr;
typedef struct node{
    char data;
    int tf;
    nptr left;
    nptr right;
}node;

nptr root = NULL;
int a,b,c;

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
    if(strchr("&|",data)){
        nptr newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->right = pop();
        newnode->left = pop();
        push(newnode);
    }
    else if(data=='~'){
        nptr newnode = (nptr)malloc(sizeof(node));
        newnode->data = data;
        newnode->right = pop();
        newnode->left = NULL;
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

void postfixsearch(nptr* nodeptr){
    nptr node = *nodeptr;
    if(!node) return;

    postfixsearch(&node->left);
    postfixsearch(&node->right);
    switch (node->data){
        case '~':
            node->tf=!node->right->tf;
            break;
        case '&':
            node->tf=node->left->tf&&node->right->tf;
            break;
        case '|':
            node->tf=node->left->tf||node->right->tf;
            break;
        default:
            if(node->data==var[0]) node->tf=a;
            else if(node->data==var[1]) node->tf=b;
            else if(node->data==var[2]) node->tf=c;
    }
}



int main(){
    FILE* fp = fopen("input.txt","r");
    char str[90];

    fscanf(fp,"%s",str);
    printf("input string: %s\n",str);

    int len = strlen(str);
    for(int i=0; i<len; i++){
        insert(&root,str[i]);
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')){
            if(var[0]==str[i]) continue;
            else if(var[1]==str[i]) continue;
            else if(var[2]==str[i]) continue;
            else if(!var[0]) var[0]=str[i];
            else if(!var[1]) var[1]=str[i];
            else if(!var[2]) var[2]=str[i];
        }
    }
    root = pop();

    printf("find ture condition\n");
    for(a=0; a<2; a++){
        for(b=0; b<2; b++){
            for(c=0; c<2; c++){
                postfixsearch(&root);
                if(root->tf)
                    printf("%c=%d, %c=%d, %c=%d\n",var[0],a,var[1],b,var[2],c);
            }
        }
    }
}