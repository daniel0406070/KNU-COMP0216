#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 100
#define MEMORY_SIZE 10
#define MAX_STACKS 10

typedef struct element{
    int id;
    char name[MAX_NAME_SIZE];
}element;

element memory[MEMORY_SIZE];
int top[MAX_STACKS];
int boundary[MAX_STACKS+1];
int n;

void init(){
    top[0] = boundary[0] = 0;
    for(int i=1; i<n; i++){
        top[i] = boundary[i] = (MEMORY_SIZE/n)*i;
    }
    boundary[n] = MEMORY_SIZE;
}

void stack_full(int i){
    printf("stack %d is full\n\n", i);
}

element stack_empty(int i){
    element e;
    e.id = -1;
    strcpy(e.name, "empty");
}

void push(int i, element item){
    if(top[i] == boundary[i+1]){
        stack_full(i);
        return;
    }
    memory[top[i]++] = item;
    printf("%s is Pushed in Stack No. %d\n", item.name, i);
}

element pop(int i){
    if(top[i]+1 == boundary[i]){
        return stack_empty(i);
    }
    return memory[--top[i]];   
}

void sprint(int i){
    for(int j=top[i]-1; j>=boundary[i]; j--){
        printf("%s\n", memory[j].name);
    }
    printf("\n");
}

void sprint_all(){
    for(int i=0; i<n; i++){
        printf("stack %d :\n", i);
        sprint(i);
        printf("\n");
    }
}

void quit(){
    printf("Program end\n");
    sprint_all();
    exit(1);
}

int main(){
    FILE *input = fopen("input.txt", "r");

    printf("How many stacks? : ");
    scanf("%d", &n);

    init();

    int id;
    char name[MAX_NAME_SIZE];
    char op[MAX_NAME_SIZE];
    int idx=0;

    while(fscanf(input, "%s", op) != EOF){
        if(strcmp(op, "add") == 0){
            fscanf(input, "%d",&id);
            fscanf(input, "%s", name);
            element e;
            e.id = ++idx;
            strcpy(e.name, name);

            if(id>=n || id<0){
                printf("stack number error, try again\n");
                continue;
            }
            push(id, e);
        }else if(strcmp(op, "delete") == 0){
            fscanf(input, "%d", &id);
            if(id>=n || id<0){
                printf("stack number error, try again\n");
                continue;
            }
            element e = pop(id);
            printf("%s is popped from Stack No. %d\n", e.name, id);
        }else if(strcmp(op, "sprint") == 0){
            fscanf(input,"%d", &id);
            if(id>=n || id<0){
                printf("stack number error, try again\n");
                continue;
            }
            sprint(id);
        }else if(strcmp(op, "quit") == 0){
            quit();
        }else{
            while(fgetc(input) != '\n');
            printf("wrong command, try again!!\n");
        }
    }


    fclose(input);
    exit(0);
}