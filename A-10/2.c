#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int data;
    struct node *rnext;
    struct node *lnext;
}node;

void insert(nptr* root, int data){
    nptr new = (nptr)malloc(sizeof(node));
    new->data = data;
    new->rnext = NULL;
    new->lnext = NULL;

    if((*root)->rnext == NULL){
        new->lnext = *root;
        new->rnext = *root;
        (*root)->rnext = new;
        (*root)->lnext = new;
    }else{
        new->lnext = (*root)->lnext;
        new->rnext = *root;
        (*root)->lnext->rnext = new;
        (*root)->lnext = new;
    }
}

void printnodes(nptr *rootptr, int option){
    nptr temp;
    if(option == 0) temp = (*rootptr)->rnext;
    else temp = (*rootptr)->lnext;
    
    if(option == 0) printf("Forward\n");
    else printf("Backward\n");

    while(temp != *rootptr){
        printf("(%08x  ", temp);
        printf("%2d", temp->data);
        printf(" %08x)  \n", option?temp->lnext:temp->rnext);
        if(option == 0) temp = temp->rnext;
        else temp = temp->lnext;
    }
    printf("\n");
}

void delete_lessequal(nptr *rootptr, int data){
    printf("Deleting nodes with data less than or equal to %d\n", data);
    nptr temp = (*rootptr)->rnext;
    while(temp != *rootptr){
        if(temp->data <= data){
            temp->lnext->rnext = temp->rnext;
            temp->rnext->lnext = temp->lnext;
            nptr del = temp;
            temp = temp->rnext;
            free(del);
        }else{
            temp = temp->rnext;
        }
    }
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    nptr root = (nptr)malloc(sizeof(node));
    root->data = 0;
    root->rnext = NULL;

    int data;
    while(fscanf(fp, "%d", &data) != EOF){
        insert(&root, data);
    }

    printf("Original\n");
    printnodes(&root, 0);
    printnodes(&root, 1);

    int del=50;
    delete_lessequal(&root, del);

    printnodes(&root, 0);
    printnodes(&root, 1);
}