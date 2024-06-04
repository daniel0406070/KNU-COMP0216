#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hesh{
    char item[100];
    int key;
} hesh;

hesh ht[11]={0};

unsigned int stringToInt(char *key){
    /* simple additive approach to create a natural number
    that is within the integer range */
    int number = 0;
    while( *key )
        number += *key++;

    return number;
}

int hash(char *str){
    int key = stringToInt(str);
    int place = key % 11;
    while(ht[place].key != 0){
        place = (place + 1) % 11;
    }
    ht[place].key = key;
    strcpy(ht[place].item, str);

    return place;
}

int main(){
    FILE *file = fopen("input.txt", "r");

    printf("input strings : ");
    char str[100];
    while(fscanf(file, "%s", str) != EOF){
        hash(str);
        printf("%s ", str);
    }
    printf("\n\n");

    printf("         %10s %10s\n","item", "key");
    for(int i = 0; i < 11; i++){
        if(ht[i].key) printf("ht[%2d] : %10s %10d\n", i, ht[i].item, ht[i].key);
        else printf("ht[%2d] :\n", i);
    }
    printf("\n");

    printf("string to search >> ");
    scanf("%s", str);
    int key = stringToInt(str);
    int place = key % 11;
    int i = 1;
    while(strcmp(ht[place].item, str) != 0){
        place = (place + 1) % 11;
        i++;
        if(i > 11){
            printf("it doesn`t exist\n");
            return 0;
        }
    }
    printf("item: %s, key: %d, ", ht[place].item, ht[place].key);
    printf("the number of comparisons: %d\n", i);
}