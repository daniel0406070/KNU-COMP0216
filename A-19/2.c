#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int data;
    nptr next;
}node;

nptr* graph;

void printnode(nptr n){
    if(n==NULL) return;
    printf("%d", n->data);

    printf("->");
    printnode(n->next);
}

void topSort(int vertex){
    int top = 0;
    int* stack = (int*)malloc(vertex*sizeof(int));

    for(int i=0; i<vertex; i++){
        if(graph[i]->data==0){
            stack[top++] = i;
        }
    }

    for(int i=0; i<vertex; i++){
        if(top==0){
            printf("Cycle detected\n");
            return;
        }

        int cur = stack[--top];
        printf("%d ", cur);
        if(graph[cur]->next!=NULL){
            printf("-> ");
        }

        for(nptr j=graph[cur]->next; j!=NULL; j=j->next){
            if(--graph[j->data]->data==0){
                stack[top++] = j->data;
            }
        }
    }
    printf("\n");

}

int main(){
    FILE* f = fopen("input.txt", "r");

    int vertex;

    fscanf(f, "%d", &vertex);
    graph = (nptr*)malloc(vertex*sizeof(nptr));
    for(int i=0; i<vertex; i++){
        graph[i] = (nptr)malloc(sizeof(node));
        graph[i]->data = 0;
        graph[i]->next = NULL;
    }

    int u, v;
    while(fscanf(f, "%d %d", &u, &v)!=EOF){
        nptr new = (nptr)malloc(sizeof(node));
        new->data = v;
        new->next = NULL;

        nptr cur = graph[u];
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = new;

        graph[v]->data++;
    }
    fclose(f);

    topSort(vertex);





}