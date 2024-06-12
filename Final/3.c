#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m;

typedef struct node* nptr;
typedef struct node {
	int data;
	nptr next;
} node;

nptr* edges = NULL;
int* visit;

void dfs(int a) {
	visit[a] = 1;
	printf("%d ", a);

	nptr tmp = edges[a];
	while (tmp){
		if (!visit[tmp->data]) dfs(tmp->data);
		tmp = tmp->next;
	}
}

int main() {
	FILE* fp = fopen("input3.txt", "r");

	fscanf(fp, "%d %d", &n, &m);
	edges = (nptr*)malloc(sizeof(nptr) * n);
	visit = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++){
		edges[i] = NULL;
		visit[i] = 0;
	}

	int a, b;
	nptr tmp;
	for (int i = 0; i < m; i++){
		fscanf(fp, "%d %d", &a, &b);
		tmp = (nptr)malloc(sizeof(node));
		tmp->next = edges[a];
		tmp->data = b;
		edges[a] = tmp;

		tmp = (nptr)malloc(sizeof(node));
		tmp->next = edges[b];
		tmp->data = a;
		edges[b] = tmp;
	}

	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	for (int i = 0; i < n; i++){
		tmp = edges[i];
		
		printf("graph[%d] : ", i);
		while (tmp!=NULL) {
			printf("%3d ", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
	}
	printf("\n");

	printf("<<<<<<<<<< Depth First Search >>>>>>>>>>\n");
	printf("dfs(1) : ");
	dfs(1);
	printf("\n\n");


	printf("<<<<<<<<<< number of vertex degree >>>>>>>>>>\n");
	for (int i = 0; i < n; i++) {
		tmp = edges[i];

		printf("vertex %d : ", i);

		int cnt = 0;
		while (tmp != NULL) {
			cnt++;
			tmp = tmp->next;
		}
		printf("%d °³\n", cnt);
	}
	printf("\n");
}