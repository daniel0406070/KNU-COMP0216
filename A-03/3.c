#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct human* humanPtr;
typedef struct human{
    char name[10];
    int age;
    float salary;
} human;

int hmansEqual(humanPtr h1, humanPtr h2){
    if(strcmp(h1->name, h2->name) != 0) return 0;
    if(h1->age != h2->age) return 0;
    if(h1->salary != h2->salary) return 0;
    return 1;
}


int main(){
    human h1, h2;

    printf("이름, 나이, 급여를 입력하세요: \n");
    fgets(h1.name, sizeof(h1.name), stdin);
    h1.name[strlen(h1.name) - 1] = '\0';

    scanf_s("%d", &h1.age);
    scanf_s("%f", &h1.salary);
    while(getchar() != '\n');

    printf("이름, 나이, 급여를 입력하세요: \n");
    fgets(h2.name, sizeof(h2.name), stdin);
    h2.name[strlen(h2.name) - 1] = '\0';
    
    scanf_s("%d", &h2.age);
    scanf_s("%f", &h2.salary);
    

    if(hmansEqual(&h1, &h2))
        printf("두 사람은 같은 사람입니다.\n");
    else
        printf("두 사람은 다른 사람입니다.\n");
    
}