#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int data;
    nptr next;
} node;
nptr root = NULL;


void insert(nptr temp){
    if(!root){
        root = temp;
        return;
    }
    if(root->data>temp->data){
        temp->next = root;
        root = temp;
        return;
    }

    nptr p = root;
    while(p->next&&p->next->data<temp->data){
        p = p->next;
    }
    temp->next = p->next;
    p->next = temp;
}

void remode_odd(){
    while(root->data%2){
        nptr temp = root;
        root = root->next;
        free(temp);
    }

    nptr p = root;
    while(p){
        if(p->next&&p->next->data%2){
            nptr temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        else{
            p = p->next;
        }
    }

    
}

void printll(){
    nptr p = root;
    while(p){
        printf("(%08x %3d %08x)\n", p, p->data, p->next);
        p = p->next;
    }
    printf("\n");
}

void deleteall(){
    nptr p = root;
    while(p){
        nptr temp = p;
        p = p->next;
        free(temp);
    }
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if(!fp){
        printf("File not found\n");
        return 0;
    }

    int data;
    while(fscanf(fp, "%d", &data) != EOF){
        nptr temp = (nptr)malloc(sizeof(node));
        temp->data = data;
        temp->next = NULL;

        insert(temp);
    }
    printll();

    remode_odd();
    printf("After removing odd numbers\n");
    printll();

    deleteall();
}