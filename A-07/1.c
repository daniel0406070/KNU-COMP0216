#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack[1000];
int top = -1;

void push(int x){
    stack[++top] = x;
}

int pop(){
    return stack[top--];
}



int main(){
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    fprintf(output, "postfix expression : ");
    printf("postfix expression : ");

    char str[80];
    while(fscanf(input,"%s", str) != EOF){
        fprintf(output, "%s ", str);
        printf("%s ", str);
        if(strcmp(str, "+") == 0){
            int a = pop();
            int b = pop();
            push(a + b);
        }else if(strcmp(str, "-") == 0){
            int a = pop();
            int b = pop();
            push(b - a);
        }else if(strcmp(str, "*") == 0){
            int a = pop();
            int b = pop();
            push(a * b);
        }else if(strcmp(str, "/") == 0){
            int a = pop();
            int b = pop();
            push(b / a);
        }else if(strcmp(str, "%%") == 0){
            int a = pop();
            int b = pop();
            push(b % a);
        }else{
            push(atoi(str));
        }   
    }

    fprintf(output, "\nthe evaluation : %d\n", stack[top]);
    printf("\nthe evaluation : %d\n", stack[top]);

    fclose(input);
    fclose(output);


}