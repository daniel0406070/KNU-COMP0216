#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int** make2dArray(int rows, int cols)
{
    int **ipp;
    int i, j;

    ipp = (int**)malloc(rows * sizeof(int*));
    if (ipp == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(1);
    }

    for (i = 0; i < rows; i++) {
        ipp[i] = (int*)malloc(cols * sizeof(int));
        if (ipp[i] == NULL) {
            printf("메모리 할당에 실패했습니다.\n");
            exit(1);
        }
    }

    srand((unsigned)time(NULL));
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            ipp[i][j] = rand() % 100;

    return ipp;
}

int main()
{
    int **ipp;
    int i, j, rows, cols;

    printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
    scanf_s("%d %d",&rows, &cols);

    ipp=make2dArray(rows, cols);
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++)
            printf("ipp[%d][%d] =%2d ", i, j, ipp[i][j]);
        printf("\n");
    }
    return 0; // break point 설정
}