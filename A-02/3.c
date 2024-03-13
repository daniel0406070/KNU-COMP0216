#include <stdio.h>
#include <time.h>
#define MAX_SIZE 2001

void sort(int arr[], int size){
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
}

void main(void){
    int i, n, step=10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;

    printf("    n   repeatition    time\n");
    for(n=0; n<=2000; n+=step){
        long repeatition = 0; 
        start = clock();
        do{
            repeatition++;

            for(i=0;i<n;i++)
                a[i] = n-i;

            sort(a,n);
        } while(clock()-start<1000);
        duration=((double)(clock() - start))/CLOCKS_PER_SEC;
        duration /= repeatition;
        printf("%6d %9d %f\n",n,repeatition,duration);
        if(n==100)step=100;
    }
}