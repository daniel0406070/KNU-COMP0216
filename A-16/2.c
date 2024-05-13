#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node {
    int mark;
    int v1;
    int v2;
    nptr l1;
    nptr l2;
} node;

void printgraph(nptr* arr, int n, int op){
    for (int i = 0; i < n; i++) {
        int a;
        printf("%d : ", i);
        nptr cur = arr[i];
        while (cur != NULL) {
            if(!op) printf("(%d, %d) ", cur->v1, cur->v2);
            if(cur->v1==i){
                a=cur->v2;
                cur = cur->l1;
            }
            else{
                a=cur->v1;
                cur = cur->l2;
            }
            if(op) printf("(%d, %d) ", i, a);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    FILE* fp = fopen("input.txt", "r");

    int n, m;
    fscanf(fp, "%d %d", &n, &m);

    nptr* arr = (nptr*)malloc(sizeof(nptr) * n);
    for (int i = 0; i < n; i++){
        arr[i] = NULL;
    }

    int x, y;
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%d %d", &x, &y);
        nptr new = (nptr)malloc(sizeof(node));
        new->v1 = x;
        new->v2 = y;
        new->l1 = NULL;
        new->l2 = NULL;
        if(arr[x]==NULL) arr[x] = new;
        else{
            nptr cur = arr[x];
            while (1){
                if(cur->v1==x && cur->l1==NULL){
                    cur->l1 = new;
                    break;
                }
                if(cur->v2==x && cur->l2==NULL){
                    cur->l2 = new;
                    break;
                }

                if(cur->v1==x) cur = cur->l1;
                else cur = cur->l2;
            }
        }
        
        if(arr[y]==NULL) arr[y] = new;
        else{
            nptr cur = arr[y];
            while (1){
                if(cur->v1==y && cur->l1==NULL){
                    cur->l1 = new;
                    break;
                }
                if(cur->v2==y && cur->l2==NULL){
                    cur->l2 = new;
                    break;
                }

                if(cur->v1==y) cur = cur->l1;
                else cur = cur->l2;
            }
        }
    }

    printf("<<<<<<<<<<<<<<간선 출력>>>>>>>>>>>>>>\n");


    printgraph(arr, n, 0);
    printgraph(arr, n, 1);

}