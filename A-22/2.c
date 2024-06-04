#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 8

int ht[HASH_SIZE] = {0};
int seed;

int pseudoRandom(int item){
    return (item * (HASH_SIZE*seed*4+seed+11)) % (HASH_SIZE-1) + 1;
}

int main(){
    FILE *file = fopen("input.txt", "r");

    printf("key sequence from file : ");
    int num[100];
    int idx = 0;
    while(fscanf(file, "%d", &num[idx++]) != EOF);
    idx--;
    for(int i = 0; i < idx; i++){
        printf("%4d ", num[i]);
    }
    printf("\n");

    printf("input seed >> ");
    scanf("%d", &seed);

    for(int i = 1; i < HASH_SIZE; i++){
        printf("randNum[%d] = %d\n", i, pseudoRandom(i));
    }
    printf("\n");

    for(int i = 0; i < idx; i++){
        int place = num[i] % HASH_SIZE;
        while(ht[place] != 0){
            place = (place + pseudoRandom(num[i])) % HASH_SIZE;
        }
        ht[place] = num[i];
    }

    printf("         %10s\n","key");
    for(int i = 0; i < HASH_SIZE; i++){
        if(ht[i]) printf("ht[%2d] : %10d\n", i, ht[i]);
        else printf("ht[%2d] :\n", i);
    }
    printf("\n");

    int key;
    while(1){
        printf("input 0 to quit\n");
        printf("key to search >> ");
        scanf("%d", &key);
        if(key == 0) break;

        int place = key % HASH_SIZE;
        int i = 1;
        while(ht[place] != key){
            place = (place + pseudoRandom(key)) % HASH_SIZE;
            i++;

            if(i > HASH_SIZE){
                printf("key not found\n\n");
                break;
            }
        }
        if(ht[place] == key){
            printf("key : %d, the number of comparisons : %d\n", key, i);
            printf("\n"); 
        }
    }
}