#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct term {
    int row;
    int col;
    int val;
} term;


void readSparseMatrix(term** sparsep, FILE* file) {
    int i, j;
    term* sparse;
    term temp;
    fscanf(file, "%d %d %d", &temp.row, &temp.col, &temp.val);
    if(temp.val==NULL) temp.val=0;
    sparse = (term*)malloc(sizeof(term) * (temp.val + 1));
    sparse[0].row = temp.row;
    sparse[0].col = temp.col;
    sparse[0].val = temp.val;
    for (i = 0; i < sparse[0].val; i++) {
        fscanf(file, "%d %d %d", &sparse[i + 1].row, &sparse[i + 1].col, &sparse[i + 1].val);
    }

    *sparsep = sparse;
}

void transpose(term* a, term* b) {
    int n, i, j, currentb;
    int* row_terms = (int*)malloc(sizeof(int) * a[0].col);
    int* starting_pos = (int*)malloc(sizeof(int) * a[0].col);
    n = a[0].val;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].val = n;
    for (i = 0; i < a[0].col; i++) {
        row_terms[i] = 0;
        starting_pos[i] = 0;
    }
    starting_pos[0] = 1;

    for (i = 1; i <= n; i++) {
        row_terms[a[i].col]++;
    }
    for (i = 1; i < a[0].col; i++) {
        starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }

    for (i = 1; i <= n; i++) {
        j = starting_pos[a[i].col]++;
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].val = a[i].val;
    }
}

void printSparseMatrix_to2DMatrix(term* sparse) {
    int i, j, k = 1;

    for (i = 0; i < sparse[0].row; i++) {
        for (j = 0; j < sparse[0].col; j++) {
            if (i == sparse[k].row && j == sparse[k].col) {
                printf("%4d ", sparse[k].val);
                k++;
            }
            else {
                printf("   0 ");
            }
        }
        printf("\n");
    }
}

void writeSparseMatrix(term* sparse, FILE* file) {
    int i;
    fprintf(file, "%d %d %d\n", sparse[0].row, sparse[0].col, sparse[0].val);
    for (i = 1; i <= sparse[0].val; i++) {
        fprintf(file, "%d %d %d\n", sparse[i].row, sparse[i].col, sparse[i].val);
    }
}

int main() {
    FILE* file_a = fopen("a.txt", "r");
    term* a;
    readSparseMatrix(&a, file_a);

    printf("A\n");
    printSparseMatrix_to2DMatrix(a);
    fclose(file_a);

    FILE* file_b = fopen("b.txt", "w");
    term* b = (term*)malloc(sizeof(term) * (a[0].val + 1));
    transpose(a, b);

    printf("B\n");
    printSparseMatrix_to2DMatrix(b);
    writeSparseMatrix(b, file_b);
    fclose(file_b);

}