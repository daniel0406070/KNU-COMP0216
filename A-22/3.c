#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 11

typedef struct hesh *hptr;
typedef struct hesh{
    char item[100];
    int key;
    hptr next;
} hesh;

hptr ht[HASH_SIZE]={0};

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
    int place = key % HASH_SIZE;

    if(!ht[place]){
        ht[place] = (hptr)malloc(sizeof(hesh));
        ht[place]->key = key;
        strcpy(ht[place]->item, str);
        ht[place]->next = NULL;
        return place;
    }

    hptr temp = ht[place];
    while(temp->next){
        temp = temp->next;
    }
    temp->next = (hptr)malloc(sizeof(hesh));
    temp = temp->next;
    temp->key = key;
    strcpy(temp->item, str);
    temp->next = NULL;

    return place;
}

int main(){
    FILE *file = fopen("input.txt", "r");

    for(int i = 0; i < HASH_SIZE; i++){
        ht[i]=NULL;
    }

    printf("input strings : ");
    char str[100];
    while(fscanf(file, "%s", str) != EOF){
        hash(str);
        printf("%s ", str);
    }
    printf("\n\n");

    printf("         %s %s\n","item", "key");
    for(int i = 0; i < HASH_SIZE; i++){
        hptr temp = ht[i];
        if(temp){
            printf("ht[%2d] : ", i);
            while(temp){
                printf("(%s %d)  ", temp->item, temp->key);
                temp = temp->next;
            }
            printf("\n");
        }
        else printf("ht[%2d] :\n", i);
    }
    printf("\n");

    while(1){
        printf("input \"quit\" to quit\n");
        printf("string to search >> ");
        scanf("%s", str);
        if(!strcmp(str, "quit")) break;

        int key = stringToInt(str);
        int place = key % HASH_SIZE;
        int i = 1;
        hptr temp = ht[place];
        while(1){
            if(!temp){
                printf("it doesn`t exist\n\n");
                break;
            }
            if(temp->key == key){
                printf("item: %s, key: %d, ", temp->item, temp->key);
                printf("the number of comparisons: %d\n\n", i);
                break;
            }
            temp = temp->next;
            i++;
        }
    }
}