#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

typedef struct term* termptr;
typedef struct term{
    float coef;
    int expon;
} term;
term terms[MAX_TERMS];
int items[3]={0,};
int avail = 0;

void poly_add(){ 
    int i=0;
    int j=items[0];
    while (i<items[0] && j<items[1]+items[0]){
        if(terms[i].expon == terms[j].expon){
            terms[avail].coef = terms[i].coef + terms[j].coef;
            terms[avail++].expon = terms[i].expon;
            i++;
            j++;
            items[2]++;
        }
        else if(terms[i].expon > terms[j].expon){
            terms[avail].coef = terms[i].coef;
            terms[avail++].expon = terms[i].expon;
            i++;
            items[2]++;
        }
        else{
            terms[avail].coef = terms[j].coef;
            terms[avail++].expon = terms[j].expon;
            j++;
            items[2]++;
        }
    }

    while(i<items[0]){
        terms[avail].coef = terms[i].coef;
        terms[avail++].expon = terms[i].expon;
        i++;
        items[2]++;
    }

    while(j<items[1]+items[0]){
        terms[avail].coef = terms[j].coef;
        terms[avail++].expon = terms[j].expon;
        j++;
        items[2]++;
    }

}

void poly_print(char ch[]) {
    
    int i=0;
    int j=0;
    int k=0;
    while (i < avail) {
        if(i==k){
            printf("\n%c(x) = ", ch[j]);
            k+=items[j++];
        }
        printf("%3.0f", terms[i].coef);
        if(terms[i].expon) printf("x^%d ", terms[i].expon);
        if(i!=k-1)
            printf("+ ");
        i++;
    }
    
    printf("\n");
}

int main(){
    char ch[3] = {'A', 'B', 'D'};

    printf("<< D(x) = A(x) + B(x) >>\n");
    for (int i = 0; i < 2; i++) {
        printf("Input the number of items of %c(x) : ", ch[i]);
        scanf_s("%d", &items[i]);
    }

    printf("input in descending order\n");
    for (int i = 0; i < 2; i++) {
        printf("coefficient and exponent of %c(x)=", ch[i]);
        printf("10x^5+8x^3+7 (10 5, 8 3, 7 0 ) : ");
        for (int j = 0; j < items[i]; j++) {
            scanf_s("%f %d", &terms[avail].coef, &terms[avail].expon);
            avail++;
        }
    }
    printf("\n");

    poly_add();
    poly_print(ch);
}