#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int** queue;
int* front;
int* rear;

void enqueue(int data, int idx){
    queue[idx][front[idx]++] = data;
}

int dequeue(int idx){
    return queue[idx][rear[idx]++];
}

void queueInit(int n){
    queue = (int**)malloc(sizeof(int*)*10);
    front = (int*)malloc(sizeof(int)*10);
    rear = (int*)malloc(sizeof(int)*10);
    for(int i = 0; i < 10; i++){
        queue[i] = (int*)malloc(sizeof(int)*n);
        front[i] = 0;
        rear[i] = 0;
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void radixSort(int *arr, int n, int d){
    for(int i = 0; i < d; i++){
        printf("Step %d 자리 --- \n", i);

        int div = 10;
        for(int j = 0; j < i; j++){
            div *= 10;
        }

        for(int j = 0; j < n; j++){
            enqueue(arr[j], (arr[j]%div)/(div/10));
        }

        int max = 0;
        for(int k = 0; k < 10; k++){
            if(front[k]-rear[k] > max){
                max = front[k]-rear[k];
            }
        }

        printf("Queue의 내용 ---\n");
        for(int k = 0; k < 10; k++){
            printf("%4d ", k);
        }
        printf("\n");
        
        for(int k = max-1; k >=0; k--){
            for(int l = 0; l < 10; l++){
                if(front[l]-rear[l] > k){
                    printf("%4d ", queue[l][rear[l]+k]);
                }else{
                    printf("     ");
                }
            }
            printf("\n");
        }
        printf("-------------------------------------------------\n");

        int idx = 0;
        for(int j = 0; j < 10; j++){
            while(front[j]>rear[j]){
                arr[idx++] = dequeue(j);
            }
        }
        for(int k = 0; k < n; k++){
            printf("%4d ", arr[k]);
        }
        printf("\n\n");
    }
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if(fp==NULL){
        printf("File Open Error\n");
        return 0;
    }

    int d,n;
    fscanf(fp, "%d %d", &d, &n);

    int *arr = (int*)malloc(sizeof(int)*n);
    queueInit(n);
    for(int i = 0; i < n; i++){
        fscanf(fp, "%d", &arr[i]);
    }

    printf("input data ---\n");
    for(int i = 0; i < n; i++){
        printf("%4d ", arr[i]);
    }
    printf("\n\n");

    radixSort(arr, n, d);
}