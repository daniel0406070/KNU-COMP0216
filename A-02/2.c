#include <stdio.h>
#include <time.h>
#define MAX_SIZE 2001

void sort(int arr[], int size) {
    int min;
    for (int i = 0; i < size; i++) {
        min = i;
        for (int j = i; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

void main(void) {
    int i, n, step = 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;

    printf("    n   time\n");
    for (n = 0; n <= 2000; n += step) {
        for (i = 0; i < n; i++)
            a[i] = n - i;

        start = clock();
        sort(a, n);
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        printf("%6d    %f\n", n, duration);
        if (n == 100)step = 100;
    }
}