#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n;



void merge(int *arr){
    int* temp = (int*)malloc(sizeof(int) * n);

    for(int i = 1; i < n; i*=2){
        printf("segment size: %d\n", i);
        for(int j = 0; j < n; j+=2*i){
            int left = j;
            int right = j + i;
            int end = j + 2*i;
            if(right > n){
                right = n;
            }
            if(end > n){
                end = n;
            }

            int l = left;
            int r = right;
            int k = left;

            while(l < right && r < end){
                if(arr[l] < arr[r]){
                    temp[k++] = arr[l++];
                }else{
                    temp[k++] = arr[r++];
                }
            }

            while(l < right){
                temp[k++] = arr[l++];
            }

            while(r < end){
                temp[k++] = arr[r++];
            }

        }
        if(i%2 == 0) printf("%11s : ","a");
        else printf("%11s : ","temp");
        for(int k = 0; k < n; k++){
            printf("%2d ", arr[k]);
        }
        printf("\n");
        
        if(i%2 == 0) printf("%11s : ","temp");
        else printf("%11s : ","a");
        for(int k = 0; k < n; k++){
            printf("%2d ", temp[k]);
        }
        printf("\n\n");

        int *t = arr;
        arr = temp;
        temp = t;
    }

    free(temp);
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

    merge(arr);

    printf("<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>>\n");
    for(int i = 0; i < n; i++){
        printf("%3d ", arr[i]);
    }
    printf("\n");
}