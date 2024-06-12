#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flower {
	char name[20];
	char cname[20];
	int price;
} flower;

int cmp(const void* a, const void* b) {
	flower aa = *(flower*)a;
	flower bb = *(flower*)b;

	return aa.price - bb.price;
}

int main() {
	FILE* fp = fopen("input1.txt", "r");

	int n;
	fscanf(fp, "%d", &n);

	flower* fs = (flower*)malloc(sizeof(flower) * n);

	for (int i = 0; i < n; i++) {
		fscanf(fp, "%s %s %d", fs[i].name, fs[i].cname, &(fs[i].price));
	}

	char a;
	char name[20];
	while (1){
		printf("게속 할까요 (y/n): ");
		scanf("%c", &a);
		while (getchar() != '\n');
		if (a == 'n') break;

		printf("찾을꽃 이름을 쓰시오 :");
		scanf("%s", name);
		while(getchar()!='\n');

		int c = 0;
		for (int i = 0; i < n; i++) {
			if (strcmp(name, fs[i].name) == 0) {
				printf("%10s: %10s: %5d\n", fs[i].name, fs[i].cname, fs[i].price);
				c = 1;
				break;
			}
		}
		if (!c) {
			printf("%s는 구조체 배열 안에 없음\n",name);
		}

	}

	qsort(fs, n, sizeof(flower), cmp);

	for (int i = 0; i < n; i++) {
		printf("%10s: %10s: %5d\n", fs[i].name, fs[i].cname, fs[i].price);
	}

	fclose(fp);
}