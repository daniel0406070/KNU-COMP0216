#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct element* Queue;
typedef struct element{
    int id;
    char name[20];
}element;

Queue queue;
int capacity = 2;
int front;
int rear;

void qprint();
void queueFull();
void copy(Queue a, Queue b, Queue c);
void add(int id, char *name);
void delete();




int main(){
    rear = -1;
    front = capacity-1;
    queue = (Queue)malloc(sizeof(element)*capacity);

    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("File open error\n");
        return 0;
    }

    char op[20];
    int id;
    char name[20];

    while(fscanf(fp, "%s", op) != EOF){
        if(strcmp(op, "add") == 0){
            fscanf(fp, "%d %s", &id, name);
            add(id, name);
        }
        else if(strcmp(op, "delete") == 0){
            delete();
        }
        else if(strcmp(op, "quit") == 0){
            printf("end of program\n");
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


void copy(Queue a, Queue b, Queue c){
    while(a != b){
        *c++ = *a++;
    }
}

void queueFull(){
    int start;
    Queue nqueue = (Queue)malloc(sizeof(element)*capacity*2);

    start = (front+1)%capacity;
    if(start < 2){
        copy(queue+start, queue+start+capacity-1, nqueue);
    }
    else{
        copy(queue+start, queue+capacity, nqueue);
        copy(queue, queue+rear+1, nqueue+capacity-start);
    }
    front = 2*capacity-1;
    rear = capacity-2;
    capacity *= 2;
    free(queue);
    queue = nqueue;

}

void add(int id, char *name){
    rear = (rear+1)%capacity;
    if(front == rear){
        queueFull();
        rear = (rear+1)%capacity;
        
        queue[rear].id = id;
        strcpy(queue[rear].name, name);
        printf("Queue capacity is doubled\n");
        printf("Current queue capacity : %d\n", capacity);
        qprint();
        printf("\n");
    }
    else{
        queue[rear].id = id;
        strcpy(queue[rear].name, name);
    }

}

void delete(){
    if(front == rear){
        printf("Queue empty\n");
        exit(0);
    }
    front = (front+1)%capacity;
}

// void qprint(){
//     for(int i = 0; i < capacity; i++){
//         printf("%d %d %5s", i, queue[i].id, queue[i].name);
//         if(i == rear)
//             printf(" <- rear");
//         if (i == front)
//             printf(" <- front");
//         printf("\n");
//     }
//     printf("\n\n");
// }

void qprint(){
    if(front == rear){
        printf("Queue empty\n");
    }
    else if((front+1)%capacity < rear){
        for(int i = (front+1)%capacity; i <= rear; i++){
            printf("%d, %s\n", queue[i].id, queue[i].name);
        }
    }
    else if((front+1)%capacity == rear){
        printf("%d, %s\n", queue[(front+1)%capacity].id, queue[(front+1)%capacity].name);
    }
    else{
        for(int i = (front+1)%capacity; i < capacity; i++){
            printf("%d, %s\n", queue[i].id, queue[i].name);
        }
        for(int i = 0; i <= rear; i++){
            printf("%d, %s\n", queue[i].id, queue[i].name);
        }
    }
    printf("\n");
}