#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int heap[MAX] = { 0, };
int n=0;

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void insert(int data) {
	heap[++n] = data;

	for (int i = n; i > 1; i/=2){
		if (heap[i] > heap[i / 2]) swap(&heap[i], &heap[i / 2]);
	}
}

void inorder(int a) {
	if (a <= n) {
		inorder(a * 2);
		printf("%d ", heap[a]);
		inorder(a * 2 + 1);
	}
}

int main() {
	FILE* fp = fopen("input2.txt", "r");

	int tmp;

	printf("***** Create a max heap *****\n");
	while (fscanf(fp, "%d", &tmp) != EOF) {
		insert(tmp);
		for (int i = 1; i <= n; i++){
			printf("%d ", heap[i]);
		}
		printf("\n");
	}
	printf("\n");

	printf("***** inorder traversal *****\n");
	inorder(1);
	printf("\n");
}