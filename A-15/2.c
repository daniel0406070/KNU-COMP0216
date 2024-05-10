#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define max 500
#define rand() (rand() % max)
#define inf 9999
#define item(x) arr[tree[(x)]][arr_idx[tree[(x)]]]
#define RUN_NUM 10
#define RUN_LINE 8

int* tree = NULL;
int** arr = NULL;
int* arr_idx = NULL;

void build(int n){
    tree = (int*)malloc(sizeof(int) * n * 2);
    for(int i = 0; i < n * 2; i++){
        tree[i] = inf;
    }

    arr_idx = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        arr_idx[i] = 0;
    }

    for(int i = 0; i < n; i++){
        tree[n + i] = i;
    }

    for(int i = n - 1; i > 0; i--){
        tree[i] = item(i * 2) < item(i * 2 + 1) ? tree[i * 2] : tree[i * 2 + 1];
    }
}

int pop(int n) {
    int ret = arr[tree[1]][arr_idx[tree[1]]];
    arr_idx[tree[1]]<RUN_NUM ? arr_idx[tree[1]]++ : 0;
    
    for(int i = (n+tree[1])/2; i > 0; i/=2){
        tree[i] = item(i * 2) < item(i * 2 + 1) ? tree[i * 2] : tree[i * 2 + 1];
    }


    return ret;
}


void levelorder(int n){
    for(int i = 1; i < n * 2; i*=2){
        for(int j = i; j < i * 2 && j < n * 2; j++){
            printf("%d ", item(j));
        }
    }
    printf("\n");
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    printf("<<<<<<<<<<<<<<< run data >>>>>>>>>>>>>>>\n\n");

    arr=(int**)malloc(sizeof(int*)*RUN_LINE);
    for(int i=0;i<RUN_LINE;i++){
        arr[i]=(int*)malloc(sizeof(int)*(RUN_NUM+1));
        printf("%d-th run:\n",i+1);
        for(int j=0;j<RUN_NUM;j++){
            fscanf(fp,"%d",&arr[i][j]);
            printf("%3d ",arr[i][j]);
        }
        printf("\n");
        arr[i][RUN_NUM]=inf;
    }
    printf("\n");
    fclose(fp);

    build(RUN_LINE);

    printf("Level-order traversal for initial min-winner tree\n");
    levelorder(RUN_LINE);

    int* sorted = (int*)malloc(sizeof(int) * RUN_NUM * RUN_LINE);
    for(int i = 0; i < RUN_NUM * RUN_LINE; i++){
        sorted[i] = pop(RUN_LINE);
    }
    printf("sorting with min-winner tree...\n\n");

    printf("sorted result\n");
    for(int i = 0; i < RUN_NUM * RUN_LINE; i++){
        printf("%d ", sorted[i]);
        if((i+1)%RUN_NUM==0) printf("\n");
    }
    printf("\n");
}