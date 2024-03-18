#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#define MAX_COL 20
#define MAX_ROW 20

typedef struct term{
    int row;
    int col;
    int val;
} term;

term* sparse;

void readSparseMatrix(term* sparse, int row, int col, int** matrix){
    int i, j, k = 1;
    sparse[0].row = row;
    sparse[0].col = col;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            if(matrix[i][j]){
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].val = matrix[i][j];
                k++;
            }
        }
    }
    sparse[0].val = k - 1;
}

void printSparseMatrix(term* sparse){
    int i;
    for(i = 0; i <= sparse[0].val; i++){
        printf("%4d, %4d %4d\n", sparse[i].row, sparse[i].col, sparse[i].val);
    }
}

void print2DMatrix(int** matrix, int row, int col){
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    srand(time(NULL));

    int n;
    scanf("%d", &n);

    int** matrix = (int**)malloc(sizeof(int*)*MAX_ROW);
    for(int i = 0; i < MAX_ROW; i++){
        matrix[i] = (int*)malloc(sizeof(int)*MAX_COL);
        memset(matrix[i], 0, sizeof(int)*MAX_COL);
    }

    int t_row, t_col;
    for(int i = 0; i < n; i++){
        t_row = rand() % MAX_ROW;
        t_col = rand() % MAX_COL;

        matrix[t_row][t_col] = rand() % 100;
    }
    printf("Random generated matrix(%d x %d)\n", MAX_ROW, MAX_COL);
    print2DMatrix(matrix, MAX_ROW, MAX_COL);

    sparse = (term*)malloc(sizeof(term)*(n+1));
    readSparseMatrix(sparse, MAX_ROW, MAX_COL, matrix);
    
    printf("Sparse matrix\n");
    printSparseMatrix(sparse);
}