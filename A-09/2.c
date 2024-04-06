#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int book;
    int classs;
    int score;
    nptr next;
}node;

typedef struct queues* qptr;
typedef struct queues{
    nptr front;
    nptr rear;
}queues;



void insert(qptr queue, node data){
    nptr new_node = (nptr)malloc(sizeof(node));
    *new_node = data;
    new_node->next = NULL;

    if(queue->rear == NULL){
        queue->front = new_node;
        queue->rear = new_node;
    }
    else{
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

node delete(qptr queue){
    if(queue->front == NULL){
        return (node){-1,0,0,NULL};
    }
    else{
        node data = *(queue->front);
        nptr temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
        if(queue->front == NULL){
            queue->rear = NULL;
        }
        return data;
    }
}

void print_all(queues queue[], int n){
    node temp;

    printf("과목번호, 학반, 성적\n");
    for(int i = 0; i < n; i++){
        printf("******************************\n");
        temp = delete(&queue[i]);
        while(temp.book != -1){
            printf("%4d %4d %4d\n", temp.book, temp.classs, temp.score);
            temp = delete(&queue[i]);
        }
    }
}

int main(){
    queues queue[3]={NULL,};

    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("File Open Error\n");
        return -1;
    }

    int a,b,c;
    node data;

    while(!feof(fp)){
        fscanf(fp, "%d %d %d", &a, &b, &c);
        data.book = a;
        data.classs = b;
        data.score = c;
        insert(&queue[a], data);
    }

    print_all(queue, 3);

    fclose(fp);
}