#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int data;
    nptr next;
} node;


void insert(nptr temp, nptr* rootptr){
    nptr root = *rootptr;
    if(!root){
        root = temp;
        root->next = root;
        *rootptr = root;
        return;
    }

    nptr p = root;
    while(p->next != root){
        p = p->next;
    }
    p->next= temp;
    temp->next = root;

    *rootptr = root;
}

void remode_odd(nptr* rootptr){
    nptr root = *rootptr;
    nptr p = root;

    while(p->next != root){
        if(p->next->data%2){
            nptr temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        else{
            p = p->next;
        }
    }

    if(root->data%2){
        nptr temp = root;
        root = root->next;
        p->next = root;
        if(p->next == p){
            root = NULL;
        }

        free(temp);
    }

    *rootptr = root;
}

void printll(nptr root){
    nptr p = root;
    if(!p){
        return;
    }

    while(p->next != root){
        printf("(%08x %3d %08x)\n", p, p->data, p->next);
        p = p->next;
    }
    printf("(%08x %3d %08x)\n", p, p->data, p->next);
    printf("\n");
}

void deleteall(nptr* rootptr){
    nptr root = *rootptr;
    nptr p = root;
    if(!p){
        return;
    }

    while(p->next != root){
        nptr temp = p;
        p = p->next;
        free(temp);
    }
    free(p);

    *rootptr = NULL;
}

int main(){
    nptr root = NULL;

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

        insert(temp, &root);
    }
    printll(root);

    remode_odd(&root);
    printf("After removing odd numbers\n");
    printll(root);

    deleteall(&root);
}