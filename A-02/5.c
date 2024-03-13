#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 2001

void sort(int arr[], int size){
    // 삽입 정렬
    int i, j, key;
    for(i=1;i<size;i++){
        key = arr[i];
        for(j=i-1;j>=0 && arr[j]>key;j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }
}

void main(void){
    srand(time(NULL));
    int i, n, step=10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;

    printf("    n   repeatition    time\n");
    for(n=0; n<=2000; n+=step){
        printf("%6d ",n);
        for(int j=0;j<3;j++){
            long repeatition = 0; 
            start = clock();
            do{
                repeatition++;

                for(i=0;i<n;i++){
                    if(j==0) a[i] = n-i;
                    else if(j==1) a[i] = i;
                    else if(j==2) a[i] = rand();
                }

                sort(a,n);
            } while(clock()-start<1000);
            duration=((double)(clock() - start))/CLOCKS_PER_SEC;
            duration /= repeatition;
            printf("%f ",duration);
            if(n==100)step=100;
        }
        printf("\n");
    }
}