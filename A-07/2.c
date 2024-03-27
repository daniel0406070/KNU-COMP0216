#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
typedef struct {
    char item[MAX];
    int top;
} stack;
stack astack;
FILE *output;

void push(stack* s, char item);
char pop(stack* s);
int is_empty(stack* s);
int is_full(stack* s);
void postfix(char post[101]);

void push(stack* s, char item){
    if(is_full(s)) return;
    s->item[++(s->top)]=item;
}

char pop(stack* s){
    if(is_empty(s)) return '\0';
    return s->item[(s->top)--];
}

int is_empty(stack* s){
    return (s->top==-1);
}

int is_full(stack* s){
    return (s->top==MAX-1);
}

// int is_operator(char c){
//     return (c=='+' || c=='-' || c=='*' || c=='/');
// }

// int precedence(char c){
//     if(c=='(') return 0;
//     else if(c=='+' || c=='-') return 1;
//     else if(c=='*' || c=='/') return 2;
//     else return 3;
// }

void postfix(char post[101]){
    int len=strlen(post);
    char tmp;
    for(int i=0; i<len; i++){
        if(post[i]=='('){
            push(&astack,post[i]);
        }
        else if(post[i]=='+' || post[i]=='-'){
            while(!is_empty(&astack) && astack.item[astack.top]!='('){
                tmp=pop(&astack);
                printf("%c ",tmp);
                fprintf(output,"%c ",tmp);
            }
            push(&astack,post[i]);
        }
         else if(post[i]=='*' || post[i]=='/'){
            while(!is_empty(&astack) && astack.item[astack.top]!='(' && ( astack.item[astack.top]=='*' || astack.item[astack.top]=='/')){
                tmp=pop(&astack);
                printf("%c ",tmp);
                fprintf(output,"%c ",tmp);
            }
            push(&astack,post[i]);
        }
        else if(post[i]==')'){
            while(!is_empty(&astack) && astack.item[astack.top]!='('){
                tmp=pop(&astack);
                printf("%c ",tmp);
                fprintf(output,"%c ",tmp);
            }
            pop(&astack);
        }
        else{
            printf("%c ",post[i]);
            fprintf(output,"%c ",post[i]);
        }
    }
    while(!is_empty(&astack)){
        tmp=pop(&astack);
        printf("%c ",tmp);
        fprintf(output,"%c ",tmp);
    }
}

int main(){
    FILE *input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    astack.top=-1;
    char post[101];
    fscanf(input,"%s",post);
    printf("<<<<<<<<<<<<<< infix to postfix >>>>>>>>>>>>>\n");
    printf("infix expression : ");
    printf("%s\n",post);
    printf("postfix expression : ");
    postfix(post);
    printf("\n");
    fprintf(output,"\n");
    
    fclose(input);
    fclose(output);
    return 0;
}