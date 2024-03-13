#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int* arr;

void time_test(int* arr, int size){
    arr = (int*)malloc(size*sizeof(int));
    for(int k = 0; k < size; k++){
        arr[k] = rand();
    }

    clock_t bf = clock();

    int min;
    for(int i = 0; i < size; i++){
        min = i;
        for(int j = i; j < size; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        if(min != i){
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }

    clock_t af = clock();

    double time = (af - bf) / (double)CLOCKS_PER_SEC;
    printf("%6d %7lf\n", size, time);
    free(arr);
}

int main(){
    srand(time(NULL));

    double time;
    printf("%6s %7s\n", "n", "Time");
    for(int i = 0; i < 100; i+=10) time_test(arr, i);
    for(int i = 100; i <= 2000; i+=100) time_test(arr, i);
    

}