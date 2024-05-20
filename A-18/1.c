#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
    int u, v, w;
}edge;

typedef struct graph{
    int V, E;
    edge* edges;
    int *parent;
}graph;

graph* a;

int cmp_edge(const void* a, const void* b){
    return ((edge*)a)->w - ((edge*)b)->w;
}

int find(int i){
    if(a->parent[i]==i) return i;
    return find(a->parent[i]);
}

void union_edge(int x, int y){
    int xset = find(x);
    int yset = find(y);
    a->parent[xset] = yset;
}

int main(){
    FILE* f = fopen("input.txt", "r");
    a=(graph*)malloc(sizeof(graph));


    a->V=0;
    fscanf(f, "%d", &a->E);
    
    a->parent = (int*)malloc(a->E*sizeof(int));
    a->edges = (edge*)malloc(a->E*sizeof(edge));
    for(int i=0; i<a->E; i++){
        a->parent[i]=i;
        fscanf(f, "%d %d %d", &a->edges[i].u, &a->edges[i].v, &a->edges[i].w);
    }
    qsort(a->edges, a->E, sizeof(edge), cmp_edge);
    fclose(f);

    for(int i=0; i<a->E; i++){
        int x = find(a->edges[i].u);
        int y = find(a->edges[i].v);
        if(x!=y){
            union_edge(x, y);
            a->V+=a->edges[i].w;
            printf("(%d, %d) %d\n", a->edges[i].u, a->edges[i].v, a->edges[i].w);
        }
    }

    printf("\n최소비용 : %d\n", a->V);
}