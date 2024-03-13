#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void *mallocer;
#define malloc(x) (mallocer=malloc(x)); if(!(mallocer)) {printf("malloc failed\n"); exit(1);}

int main(){
    int i, *pi;
    float f, *pf;
    pi=(int*)malloc(sizeof(int));
    pf=(float*)malloc(sizeof(float));
    *pi=1024;
    *pf=3.14;
    printf("an integer=%d, a float=%f\n", *pi, *pf);
    free(pi);
    free(pf);
}