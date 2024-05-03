#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int lenmin = 0;
int pqmin[100002]= { 0, };

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void push_min(int x) { //푸쉬
	pqmin[++lenmin] = x;
	int i = lenmin;
	while (i > 1 && pqmin[i] < pqmin[i/2]) {
		swap(&pqmin[i], &pqmin[i/2]);
		i = i/2;
	}	
}

int pop_min() { //팝
	if (lenmin == 0) {
		return 0;
	}
	int ret = pqmin[1];
	pqmin[1] = pqmin[lenmin--];
	int i = 1;
	while (i * 2 <= lenmin) {
		int child;
		if (i * 2 + 1 > lenmin) child = i * 2;
		else child =  pqmin[i * 2] < pqmin[i * 2 + 1] ? i * 2 : i * 2 + 1;
		if (pqmin[i] < pqmin[child]) break;
		swap(&pqmin[i], &pqmin[child]);
		i = child;
	}
	return ret;
}

void printlist(){
    for(int i = 1; i <= lenmin; i++){
        printf("%2d ", pqmin[i]);
    }
    printf("\n");
}

int main(){
    FILE *fp = fopen("input.txt", "r");

    printf("***** insertion into a min heap *****\n");
    int n;
    while(fscanf(fp, "%d", &n) != EOF){
        push_min(n);
        printlist();
    }

    printf("***** deletion form a min heap *****\n");
    while(lenmin > 0){
        printf("delet data = %d \n", pop_min());
        printlist();
    }
}