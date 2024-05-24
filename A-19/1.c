#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define inf 999

typedef struct edge{
    int u, v, w;
}edge;

int vertex, edge_num;
int** graph;
int* weight;
int* back;
int* visited;


int main(){
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d %d", &vertex, &edge_num);
    graph = (int**)malloc(vertex*sizeof(int*));
    weight = (int*)malloc(vertex*sizeof(int));
    back = (int*)malloc(vertex*sizeof(int));
    visited = (int*)malloc(vertex*sizeof(int));

    for(int i=0; i<vertex; i++){
        graph[i] = (int*)malloc(vertex*sizeof(int));
        for(int j=0; j<vertex; j++){
            graph[i][j] = 0;
        }
        weight[i] = inf;
        back[i] = -1;
        visited[i] = 0;
    }
    weight[0] = 0;
    visited[0] = 1;
    back[0] = 0;

    int u, v, w;
    for(int i=0; i<edge_num; i++){
        fscanf(f, "%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }
    fclose(f);

    int idx = 0;
    while(1){
        int min = inf;
        
        for(int i=0; i<vertex; i++){
            if(graph[idx][i]!=inf && visited[i]==0){
                if(graph[idx][i]&&weight[i]>graph[idx][i]+weight[idx]){
                    weight[i] = graph[idx][i]+weight[idx];
                    back[i] = idx;
                }
            }
        }


        printf("%d: ", idx);
        for(int i=0; i<vertex; i++){
            printf("%5d ", weight[i]);
        }

        printf("\n");

        visited[idx] = 1;
        for(int i=0; i<vertex; i++){
            if(visited[i]==0 && min>weight[i]){
                min = weight[i];
                idx = i;
            }
        }
        
        
        if(min==inf) break;
    }

    int* path = (int*)malloc(vertex*sizeof(int));
    for(int i=1; i<vertex; i++){
        int j = i;
        int cnt = 0;
        while(1){
            path[cnt++] = j;

            if(j==0) break;
            j = back[j];
        }

        printf("distance[0->%d]=%-4d: ", i, weight[i]);
        for(int k=cnt-1; k>0; k--){
            printf("<%d->%d> ", path[k], path[k-1]);
        }
        printf("\n");
    }
    

    for(int i=0; i<vertex; i++){
        free(graph[i]);
    }
    free(graph);
}