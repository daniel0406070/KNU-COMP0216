#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 20

typedef struct node* nptr;
typedef struct node{
    char name[MAX_NAME_SIZE];
    char school[MAX_NAME_SIZE];
    int sex;
    nptr next;
} node;


void insert(nptr* rootptr,node* temp){
    temp->next = NULL;

    nptr root = *rootptr;
    if(!root){
        root = temp;
        *rootptr = root;
        return;
    }

    nptr p = root;
    while(p->next){
        p = p->next;
    }
    temp->next = p->next;
    p->next = temp;
}

void divide_sex(nptr root, nptr* manroot, nptr* wmanroot){
    nptr p = root;
    nptr pp = NULL;
    while(p){
        pp = p->next;
        if(p->sex)
            insert(manroot, p);
        else
            insert(wmanroot, p);
        p = pp;
    }
}

void merge(nptr a, nptr b){
    nptr p = a;
    while(p->next){
        p = p->next;
    }
    p->next = b;
}

void invert(nptr* rootptr){
    nptr root = *rootptr;
    nptr p = root;
    nptr pp = NULL;
    nptr ppp = NULL;
    while(p){
        ppp = pp;
        pp = p;
        p = p->next;
        pp->next = ppp;
    }
    *rootptr = pp;
}

void printll(nptr root){
    nptr p = root;
    while(p){
        printf("(%08x %s %s %s %08x)\n", p, p->name, p->school, p->sex?"남자":"여자", p->next);
        p = p->next;
    }
    printf("\n");
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if(!fp){
        printf("File not found\n");
        return 0;
    }
    nptr root = NULL;
    nptr manroot = NULL;
    nptr wmanroot = NULL;


    int tmp_name[MAX_NAME_SIZE];
    int tmp_school[MAX_NAME_SIZE];
    char tmp_sex[MAX_NAME_SIZE];

    while(fscanf(fp, "%s %s %s", tmp_name, tmp_school, tmp_sex)!=EOF){
        nptr temp = (nptr)malloc(sizeof(node));
        strcpy(temp->name, tmp_name);
        strcpy(temp->school, tmp_school);
        if(strcmp(tmp_sex,"남자")==0)
            temp->sex = 1;
        else
            temp->sex = 0;

        temp->next = NULL;

        insert(&root, temp);
    }
    printf("전체 리스트\n");
    printll(root);

    
    divide_sex(root, &manroot, &wmanroot);
    printf("남자 리스트\n");
    printll(manroot);
    printf("여자 리스트\n");
    printll(wmanroot);

    merge(wmanroot, manroot);
    printf("합친 리스트\n");
    printll(wmanroot);

    invert(&wmanroot);
    printf("뒤집은 리스트\n");
    printll(wmanroot);
}