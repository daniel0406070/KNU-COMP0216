#include <stdio.h>
#include <math.h>  

int main(int argc, char* argv[]) {
    FILE* f1 = fopen(argv[1], "r");
    int t1,t2;
    double t3;
    char tname[10];

    int a,b;
    double c;
    char name[10];
    double n;
    double min=100;
    printf("BMI 값을 쓰시오 : ");
    scanf("%lf", &n);
    printf("\n");

    printf("키\t몸무게\t이름\tBMI\n");
    printf("====================================\n");
    for (int i=0; i<10; i++){
        fscanf(f1, "%d %d %s", &a, &b, name);
        c = b/(a*a);
        printf("%d\t%d\t%s\t%.2f\n", a, b, name, c);

        if(fabs(n-c)<min){
            min = fabs(n-c);
            t1 = a;
            t2 = b;
            t3 = c;
            strcpy(tname, name);
        }
    }
    printf("\n\n");
    printf("BMI 값이 %lf에 가장 근접한 사람 :\n");
    printf("키: %d, 몸무게: %d, 이름: %s, BMI: %lf\n", t1, t2, tname, t3);
}