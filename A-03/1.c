#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int* make1dArray(int n)
{
    int* ip;

    ip = (int*)malloc(n * sizeof(int));
    if (ip == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(1);
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        ip[i] = rand() % 100;

    return ip;
}


int main()
{
    int *ipp;
    int i, num;

    printf("일차원 배열의 수를 입력하세요: ");
    scanf_s("%d", &num);

    ipp = make1dArray(num);
    for (i = 0; i < num; i++) {
        printf("ipp[%2d] =%2d ", i, ipp[i]);
        if ((i % 5) == 4)
            printf("\n");
    }

    return 0;
}