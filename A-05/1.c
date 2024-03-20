#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20

typedef struct element{
    int id;
    char name[MAX_NAME_SIZE];
}element;

element stack[MAX_STACK_SIZE];
int top = 0;

void sprint(){
    for(int i = top-1; i >=0 ; i--){
        printf("%d %s\n", stack[i].id, stack[i].name);
    }
    printf("\n\n");
}


void push(int id, char *name){
    if(top == MAX_STACK_SIZE){
        printf("Stack is full, cannot add element\n");
        printf("current stack elements : \n");
        sprint();
        exit(0);
    }
    stack[top].id = id;
    strcpy(stack[top].name, name);
    top++;
}

void pop(){
    if(top == 0){
        printf("Stack is empty, cannot delete element\n");
        printf("current stack elements : \n");
        sprint();
        exit(0);
    }
    top--;
}




int main(){
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("File open error\n");
        return 0;
    }

    char op[MAX_NAME_SIZE+5];
    int id;
    char name[MAX_NAME_SIZE];
    while(fscanf(fp, "%s", op) != EOF){
        if(strcmp(op, "push") == 0){
            fscanf(fp, "%d %s", &id, name);
            push(id, name);
        }
        else if(strcmp(op, "pop") == 0){
            pop();
        }
        else if(strcmp(op, "quit") == 0){
            exit(0);
        }
        else if(strcmp(op, "sprint") == 0){
            sprint();
        }
        else{
            printf("wrong command! try again!\n\n");
            while(fgetc(fp) != '\n');
        }
    }
}