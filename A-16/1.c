#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int data;
    nptr next;
} node;

int main(){
    FILE* fp = fopen("input.txt", "r");

    char type;
    int n, m;
    fscanf(fp, "%c %d %d", &type, &n, &m);

    nptr* arr = (nptr*)malloc(sizeof(nptr) * n);
    for(int i = 0; i < n; i++) 
        arr[i] = NULL;

    int x,y;
    for(int i = 0; i < m; i++){
        fscanf(fp, "%d %d", &x, &y);
        nptr new = (nptr)malloc(sizeof(node));
        new->data = y;
        new->next = arr[x];
        arr[x] = new;

        if(type == 'd') continue;
        nptr new2 = (nptr)malloc(sizeof(node));
        new2->data = x;
        new2->next = arr[y];
        arr[y] = new2;
    }

    printf("<<<<<<<<<<<<<<adjacency-list>>>>>>>>>>>>>>\n");
    for(int i = 0; i < n; i++){
        printf("adjList[%d] : ", i);
        nptr cur = arr[i];
        while(cur != NULL){
            printf("%2d ", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
    
}