#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define max 500
#define rand() (rand() % max)
#define inf 9999
#define item(x) arr[tree[(x)]][arr_idx[tree[(x)]]]

int* tree = NULL;
int** arr = NULL;
int* arr_idx = NULL;

void build(int n){
    tree = (int*)malloc(sizeof(int) * n * 2);
    for(int i = 0; i < n * 2; i++){
        tree[i] = inf;
    }

    arr_idx = (int*)malloc(sizeof(int) * n);
    arr = (int**)malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
        arr[i] = (int*)malloc(sizeof(int) * 2);
        
        arr[i][0] = rand();

        printf("%3d ", arr[i][0]);
        arr[i][1] = inf;
        arr_idx[i] = 0;
    }
    printf("\n\n");

    printf("initialization of min-winner tree\n");
    for(int i = 0; i < n; i++){
        tree[n + i] = i;
    }

    for(int i = n - 1; i > 0; i--){
        tree[i] = item(i * 2) < item(i * 2 + 1) ? tree[i * 2] : tree[i * 2 + 1];
    }
}

int pop(int n) {
    int ret = arr[tree[1]][arr_idx[tree[1]]];
    arr_idx[tree[1]]<1 ? arr_idx[tree[1]]++ : 0;
    
    for(int i = (n+tree[1])/2; i > 0; i/=2){
        tree[i] = item(i * 2) < item(i * 2 + 1) ? tree[i * 2] : tree[i * 2 + 1];
    }


    return ret;
}


void inorder(int n, int i){
    if(i <2*n){
        inorder(n, i * 2);
        printf("%d ", item(i));
        inorder(n, i * 2 + 1);
    }
}


int main(){
    printf("<<<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>>>\n\n");

    int k;
    printf("the number of keys (4,8,16, or 32 as power of 2 ) >> ");
    scanf("%d", &k);

    int seed;
    printf("the value of seed >>");
    scanf("%d", &seed);

    srand(seed);
    build(k);

    printf("inorder traversal for min-winner tree\n");
    inorder(k, 1);
    printf("\n");

    int* sorted = (int*)malloc(sizeof(int) * k);
    for(int i = 0; i < k; i++){
        sorted[i] = pop(k);
        if(i==1){
            printf("Winner Tree inoder traversal after find 2 winnner\n");
            inorder(k, 1);
            printf("\n");
        }
    }
    printf("sorting with min-winner tree...\n\n");

    printf("sorted result\n");
    for(int i = 0; i < k; i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");
}