#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int book;
    int classs;
    int score;
    nptr before;
}node;



void push(nptr *top, node data){
    nptr new_node = (nptr)malloc(sizeof(node));
    *new_node = data;
    new_node->before = NULL;

    if(*top == NULL){
        *top = new_node;
        return;
    }
    else{
        new_node->before = *top;
        *top = new_node;
    }
}

node pop(nptr *top){
    if(*top == NULL){
        return (node){-1,0,0,NULL};
    }
    else{
        node data = **top;
        nptr temp = *top;
        *top = (*top)->before;
        free(temp);
        return data;
    }
}

void print_all(nptr top[], int n){
    node temp;

    printf("과목번호, 학반, 성적\n");
    for(int i = 0; i < n; i++){
        printf("******************************\n");
        temp = pop(&top[i]);
        while(temp.book != -1){
            printf("%4d %4d %4d\n", temp.book, temp.classs, temp.score);
            temp = pop(&top[i]);
        }
    }
}

int main(){
    nptr top[3]={NULL,};

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
        push(&top[a], data);
    }

    print_all(top, 3);

    fclose(fp);
}