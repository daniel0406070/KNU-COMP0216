#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct offset{
    short int vert;
    short int horiz;
}offset;
offset dir[8] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int** maze;
int** mark;
int n,m;

typedef struct way{
    int vert;
    int horiz;
    int dir;
}way;
way* stack;
int top = -1;

void push(way item){
    stack[++top] = item;
}

way pop(){
    return stack[top--];
}

way peek(){
    return stack[top];
}

void init(){
    maze = (int**)malloc(sizeof(int*)*(n+2));
    maze[0] = (int*)malloc(sizeof(int)*(m+2));
    maze[n+1] = (int*)malloc(sizeof(int)*(m+2));
    for(int i=0; i<=m+1; i++){
        maze[0][i] = 1;
        maze[n+1][i] = 1;
    }
    for(int i=1; i<=n; i++){
        maze[i] = (int*)malloc(sizeof(int)*(m+2));
        maze[i][0] = 1;
        maze[i][m+1] = 1;
    }

    mark = (int**)malloc(sizeof(int*)*(n+2));
    for(int i=0; i<=n+1; i++){
        mark[i] = (int*)malloc(sizeof(int)*(m+2));
        for(int j=0; j<=m+1; j++){
            mark[i][j] = 0;
        }
    }

    stack = (way*)malloc(sizeof(way)*n*m);
}

void doyouknowtheway(){
    mark[1][1] = 1;
    way now = {1,1,0};

    while(1){

        int nextvert, nexthoriz;
        while(now.dir < 8){
            nextvert = now.vert + dir[now.dir].vert;
            nexthoriz = now.horiz + dir[now.dir].horiz;
            if(nextvert == n && nexthoriz == m){
                push(now);
                push((way){n,m,0});
                return;
            }
            if(maze[nextvert][nexthoriz] == 0 && mark[nextvert][nexthoriz] == 0){
                mark[nextvert][nexthoriz] = 1;
                push(now);
                break;
            }
            now.dir++;
        }

        if(now.dir == 8){
            now = pop();
            if(top == -1){
                printf("No path in maze\n");
                exit(0);
            }
        }
        else{
            now.vert = nextvert;
            now.horiz = nexthoriz;
            now.dir = 0;
        }

        
    }

    printf("No path in maze\n");
    exit(0);
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("File open error\n");
        return 0;
    }

    fscanf(fp,"%d %d", &n, &m);
    
    init();
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            fscanf(fp,"%d", &maze[i][j]);
        }
    }
    
    doyouknowtheway();

    printf("The path is:\n");
    printf("row col\n");
    for(int i=0; i<=top; i++){
        printf("%2d %4d\n", stack[i].vert, stack[i].horiz);
    }
}