#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101

typedef struct polynomial* polyptr;
typedef struct polynomial {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

polyptr addpoly(polyptr a, polyptr b) {
    int i;
    polyptr c;
    c = (polyptr)malloc(sizeof(polynomial));
    if (c == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(1);
    }

    c->degree = (a->degree > b->degree) ? a->degree : b->degree;
    for (i = 0; i <= c->degree; i++)
        c->coef[i] = a->coef[i] + b->coef[i];
    return c;
}

void poly_print(char ch[], polynomial a) {
    printf("%s", ch);
    for (int j = a.degree; j > 0; j--) {
        printf("%3.0fx^%d + ", a.coef[j], j);
    }
    printf("%3.0f\n", a.coef[0]);
    
}

int main() {
    polyptr a[3] = { 0, };
    int i, degree;
    float tmp[MAX_DEGREE];

    for (i = 0; i < 2; i++) {
        a[i] = (polyptr)malloc(sizeof(polynomial));
        if (a[i] == NULL) {
            printf("메모리 할당에 실패했습니다.\n");
            exit(1);
        }
        for (int j = 0; j < MAX_DEGREE; j++)
            a[i]->coef[j] = 0;
    }

    printf("<< C(x) = A(x) + B(x) >>\n");
    for (i = 0; i < 2; i++) {
        printf("다항식 %c의 최고 차수를 입력하세요: ", 'A' + i);
        scanf_s("%d", &degree);
        a[i]->degree = degree;
        printf("%c의 계수를 입력하세요: ", 'A' + i);
        for (int j = 0; j <= degree; j++) {
            scanf_s("%f", &tmp[j]);
        }
        for (int j = 0; j <= degree; j++)
            a[i]->coef[j] = tmp[degree - j];
    }

    a[2] = addpoly(a[0], a[1]);

    char ch[10] = { "A(x) = " };
    for (i = 0; i < 3; i++) {
        ch[0] = 'A' + i;
        poly_print(ch, *(a[i]));
    }
    



}