#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define STR_LEN 12

typedef struct node* nptr;
typedef struct node {
	char data[STR_LEN];
	nptr next;
	int key;
} node;


nptr* b = NULL;

unsigned int stringToInt(char* st) {
	int number = 0;
	while (*st)
		number += *st++;
	return number;
}

int hashing(int k) {
	return k % SIZE;
}

int hash(char* st) {
	int key = stringToInt(st);
	int k = hashing(key);
	
	nptr tmp = (nptr)malloc(sizeof(node));
	strcpy(tmp->data,st);
	tmp->next = NULL;
	tmp->key = key;

	if (b[k]) {
		nptr bb = b[k];
		while (bb->next) {
			bb = bb->next;
		}
		bb->next = tmp;
	}
	else {
		b[k] = tmp;
	}

}

int main() {
	FILE* fp = fopen("input4.txt", "r");

	char st[STR_LEN];
	b = (nptr*)malloc(sizeof(nptr) * SIZE);
	for (int i = 0; i < SIZE; i++) {
		b[i] = NULL;
	}

	while (fscanf(fp, "%s", st) != EOF) {
		hash(st);
	}

	nptr tmp;
	printf("<<<<<<<<<<<< Hashing Table >>>>>>>>>>>>\n\n");
	printf("          item  key\n");
	for (int i = 0; i < SIZE; i++){
		printf("ht[%2d] : ",i);
		tmp = b[i];
		while (tmp != NULL) {
			printf("(%s %d) ", tmp->data, tmp->key);
			tmp = tmp->next;
		}
		printf("\n");
	}
	printf("\n\n");

	while(1){
		printf("input \"Q\" to quit\n");
		printf("string to search >> ");
		scanf("%s", st);
		if (!strcmp("Q", st)) break;

		int key = stringToInt(st);
		int k = hashing(key);
		int cnt = 0;
		tmp = b[k];
		while (1) {
			cnt++;
			if (tmp == NULL) break;
			if (!strcmp(st, tmp->data)) break;
			tmp = tmp->next;
		}

		if (tmp) {
			printf("item: %s, key : %d, the number of comparisions : %d\n\n", tmp->data, tmp->key, cnt);
		}
		else {
			printf("it doesn`t exist!! key : %d, the number of comparisions : %d\n\n", key, cnt);
		}
	}
}