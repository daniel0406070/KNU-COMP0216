#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int data;
    nptr next;
} node;
int* visited;
nptr* arr;

int* queue=NULL;
int front, rear;

void bfs(int idx){
    front = rear = 0;
    queue[rear++] = idx;
    visited[idx] = 1;

    while(front < rear){
        int cur = queue[front++];
        printf("%d ", cur);
        nptr tmp = arr[cur];
        while(tmp != NULL){
            if(visited[tmp->data] == 0){
                queue[rear++] = tmp->data;
                visited[tmp->data] = 1;
            }
            tmp = tmp->next;
        }
    }
}

int main(){
    FILE* fp = fopen("input.txt", "r");

    int n, m;
    fscanf(fp, "%d %d", &n, &m);

    queue = (int*)malloc(sizeof(int) * n);
    visited = (int*)malloc(sizeof(int) * n);
    arr = (nptr*)malloc(sizeof(nptr) * n);
    for(int i = 0; i < n; i++) 
        arr[i] = NULL;

    int x,y;
    for(int i = 0; i < m; i++){
        fscanf(fp, "%d %d", &x, &y);
        nptr new = (nptr)malloc(sizeof(node));
        new->data = y;
        new->next = arr[x];
        arr[x] = new;

        nptr new2 = (nptr)malloc(sizeof(node));
        new2->data = x;
        new2->next = arr[y];
        arr[y] = new2;
    }
    
    for(int i = 0; i < n; i++){
        printf("%d : ", i);
        nptr cur = arr[i];
        while(cur != NULL){
            printf("%d ", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
    printf("\n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) visited[j] = 0;
        printf("BFS(%d) : ", i);
        bfs(i);
        printf("\n");
    }
}