#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Adjust(int *arr, int n, int i){
    int temp = arr[i];
    int j;
    for(j = 2*i; j <= n; j *= 2){
        if(j < n && arr[j] < arr[j+1]){
            j++;
        }
        if(temp >= arr[j]){
            break;
        }
        arr[j/2] = arr[j];
    }
    arr[j/2] = temp;
}

void HeapSort(int *arr, int n){
    printf("<<<<<<<<<<<<<<<< executing Heap Sort >>>>>>>>>>>>>>>>\n");
    for(int i = n/2; i > 0; i--){
        Adjust(arr, n, i);
    }

    printf("<<<<<<<<After initialization of max heap>>>>>>>>\n");
    for (int j = 1; j <= n; j++){
        printf("%d ", arr[j]);
    }
    printf("\n\n");

    for(int i = n; i > 1; i--){

        swap(&arr[1], &arr[i]);
        Adjust(arr, i-1, 1);

        printf("Step %d: ", n-i+1);
        printf("출력 %d : ", arr[i]);
        for (int j = 1; j < i; j++){
            printf("%2d ", arr[j]);
        }
        printf("\n");
    }

    printf("\n<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>\n");
    for(int i = 1; i < n+1; i++){
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if(fp==NULL){
        printf("File Open Error\n");
        return 0;
    }

    int n;
    fscanf(fp, "%d", &n);

    int *arr = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 1; i < n+1; i++){
        fscanf(fp, "%d", &arr[i]);
    }

    printf("<<<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>>>>\n");
    for(int i = 1; i < n+1; i++){
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    HeapSort(arr, n);
}