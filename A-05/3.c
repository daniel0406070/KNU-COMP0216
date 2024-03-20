#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
    int id; // unique id
    char name[MAX_NAME_SIZE]; //last name
} element;
element queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;

void add(int id, char *name){
    if((rear+1)%MAX_QUEUE_SIZE == front){
        printf("Queue is full, not added\n");
        return;
    }
    rear=(rear+1)%MAX_QUEUE_SIZE;
    queue[rear].id = id;
    strcpy(queue[rear].name, name);
}

void delete(){
    if(front == rear){
        printf("Queue empty\n");
        exit(0);
    }
    front=(front+1)%MAX_QUEUE_SIZE;
}

void qprint(){
    if(rear<front){
        for(int i = front+1; i < MAX_QUEUE_SIZE; i++){
            printf("%d %s\n", queue[i].id, queue[i].name);
        }
        for(int i = 0; i <= rear; i++){
            printf("%d %s\n", queue[i].id, queue[i].name);
        }
    }
    else{
        for(int i = front+1; i <= rear; i++){
            printf("%d %s\n", queue[i].id, queue[i].name);
        }
    }
    printf("\n\n");
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
        if(strcmp(op, "add") == 0){
            fscanf(fp, "%d %s", &id, name);
            add(id, name);
        }
        else if(strcmp(op, "delete") == 0){
            delete();
        }
        else if(strcmp(op, "quit") == 0){
            exit(0);
        }
        else if(strcmp(op, "qprint") == 0){
            qprint();
        }
        else{
            printf("wrong command! try again!\n");
            while(fgetc(fp) != '\n');
        }
    }
}