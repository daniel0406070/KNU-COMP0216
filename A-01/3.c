#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int* arr;
int used[1000]={0,};

int binarySearch(int *arr, double target, int n){
    int left = 0;
    int right = n-1;
    int mid = (left+right)/2;
    while(left<=right){
        if(arr[mid]==target) return mid;
        else if(arr[mid]>target) right=mid-1;
        else left=mid+1;
        mid=(left+right)/2;
    }
    return -1;
}


int main(){
    srand(time(NULL));
    int n;
    scanf("%d", &n);

    arr=(int*)malloc(sizeof(int)*n);
    for(int i=0; i<n; i++){
        int a=rand()%1000;
        while(1){
            if(used[a]==0){
                used[a]=1;
                arr[i]=a;
                break;
            }
            a=rand()%1000;
        }
    }

    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    int temp;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    int m;
    scanf("%d", &m);
    
    int idx = binarySearch(arr, m, n);
    if(idx==-1) printf("Not found");
    else printf("Found at %d", idx);

}