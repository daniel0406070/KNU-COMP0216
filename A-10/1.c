#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24

typedef struct node* nptr;
typedef struct node{
    int data;
    struct node *next;
}node;
int* result = NULL;



void init(nptr** seq, int n){
    *seq = (nptr*)malloc(sizeof(nptr)*n);
    for(int i=0; i<n; i++){
        (*seq)[i] = NULL;
    }
}

void insert(nptr** seq, int n, int data){
    nptr new = (nptr)malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    if((*seq)[n] == NULL){
        (*seq)[n] = new;
    }else{
        new->next = (*seq)[n];
        (*seq)[n] = new;
    }
}

void printnodeline(nptr* seq, int n){
    nptr temp = seq[n];
    printf("%d: \n", n);
    while(temp != NULL){
        printf("(%08x  ", temp);
        printf("%2d", temp->data);
        printf(" %08x)  ", temp->next);
        temp = temp->next;
    }
    printf("\n");
}

void delete_all(nptr** seq, int n){
    for(int i=0; i<n; i++){
        nptr temp = (*seq)[i];
        while(temp != NULL){
            nptr del = temp;
            temp = temp->next;
            free(del);
        }
    }
    free(*seq);
    *seq = NULL;
}

void find(nptr* seq, int n, int idx){
    int* stack = (int*)malloc(sizeof(int)*MAX_SIZE);
    int top = -1;

    stack[++top] = n;
    nptr temp;
    printf("R%2d   %d  ", idx, n);
    while(top != -1){
        temp = seq[stack[top--]];
        while(temp != NULL){
            if(result[temp->data] == 0){
                result[temp->data] = idx;
                stack[++top] = temp->data;
                printf("%2d  ", temp->data);
            }
            temp = temp->next;
        }
    }
    printf("\n");

    return;
}


int main(){
    nptr* seq;
    FILE *fp = fopen("input.txt", "r");
    int n;

    printf("MAX_SIZE of a set S: %d\n", MAX_SIZE);
    fscanf(fp, "%d", &n);
    init(&seq, n);
    printf("size of S: %d\n", n);
    printf("S = { ");
    for(int i=0; i<n; i++){
        printf("%d ", i);
    }
    printf("}\n");

    int a,b;
    printf("input pairs: ");
    while(fscanf(fp, "%d %d", &a, &b) != EOF){
        printf("%dR%d ", a, b);
        insert(&seq, a, b);
        insert(&seq, b, a);
    }
    printf("\n\n");

    for(int i=0; i<n; i++){
        printnodeline(seq, i);
    }
    printf("\n");

    if(result == NULL){
        result = (int*)malloc(sizeof(int)*n);
        for(int i=0; i<n; i++){
            result[i] = 0;
        }
    }

    int idx = 0;
    for(int i=0; i<n; i++){
        if(result[i] == 0){
            idx++;
            result[i] = idx;
            find(seq, i, idx);
        }
    }


    delete_all(&seq, n);
}