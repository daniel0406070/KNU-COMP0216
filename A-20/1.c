#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n;

void shell_sort(int *arr){
    int h = n/2;

    while(h > 0){
        printf("gap is %5d ====>\n", h);
        for(int i = h; i < n; i++){
            int j = i;
            int temp = arr[i];
            while(j >= h && arr[j - h] > temp){
                arr[j] = arr[j - h];
                j -= h;
            }
            arr[j] = temp;
        }

        for(int i = 0; i < n; i++){
            printf("%3d ", arr[i]);
        }
        printf("\n\n");

        h /= 2;
        if(h && h%2 == 0) h++;
    }
}

int main(){
    FILE *fp = fopen("input.txt", "r");

    fscanf(fp, "%d", &n);

    int *arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    printf("list[] data\n");
    for(int i = 0; i < n; i++){
        printf("%3d ", arr[i]);
    }
    printf("\n\n");

    shell_sort(arr);

}