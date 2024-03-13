#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE f1 = fopen(argv[1], "r");
    FILE f2 = fopen(argv[2], "r");

    int num[3][10]={0,};

    for (int i=0; i<10; i++){
        fscanf(f1, "%d", &num[0][i]);
    }
    for (int i=0; i<10; i++){
        fscanf(f2, "%d", &num[1][i]);
    }
    for (int i=0; i<10; i++){
        num[2][i] = num[0][i] + num[1][i];
    }

    for (int i=0; i<3; i++){
        for (int j=0; j<10; j++){
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }
