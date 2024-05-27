#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n;
int cnt = 0;

void qsort2(int *arr, int left, int right){
    if(left >= right) return;

    cnt++;
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    printf("pivot = %d : ", pivot);

    while(i <= j){
        while(i <= right && arr[i] <= pivot) i++;
        while(j > left && arr[j] >= pivot) j--;

        if(i > j){
            int temp = arr[j];
            arr[j] = arr[left];
            arr[left] = temp;
        }else{
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    qsort2(arr, left, j - 1);
    qsort2(arr, j + 1, right);
}

int main(){
    FILE *fp = fopen("input.txt", "r");

    fscanf(fp, "%d", &n);

    int *arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    printf("<<<<<<<<<<<<<<<<< input >>>>>>>>>>>>>>>>>\n");
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n\n");


    qsort2(arr, 0, n - 1);
    printf("call of qsort = %d\n\n", cnt);
    printf("<<<<<<<<<<<<<<<<< result >>>>>>>>>>>>>>>>>\n");
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}