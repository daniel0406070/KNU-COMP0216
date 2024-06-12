#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, m;
int** maze;
int** visit;

int top = -1;

typedef struct pos{
	int x;
	int y;
	int dir;
}pos;
pos* way;

int dir[4][2] = {
	{-1,0},
	{1,0},
	{0,-1},
	{0,1}
};

void fix() {
	way[++top] = (pos){ 0,0,0};

	while (top != -1) {
		pos now = way[top];
		if (now.x == n - 1 && now.y == m - 1) return;

		for (int i = now.dir; i < 5; i++) {
			if (i >= 4) {
				top--;
				break;
			}
			pos nn = now;
			nn.x += dir[i][0];
			nn.y += dir[i][1];

			if (nn.x < 0 || nn.x >= n || nn.y < 0 || nn.y >= m) continue;
			if (maze[nn.x][nn.y] == 1) continue;
			if (visit[nn.x][nn.y]==1)continue;

			visit[nn.x][nn.y] = 1;
			way[top].dir = i + 1;
			way[++top] = (pos){ nn.x,nn.y,0 };
			break;
		}
	}


}

int main() {
	FILE* fp = fopen("input3.txt", "r");

	fscanf(fp, "%d %d", &n, &m);

	maze = (int**)malloc(sizeof(int*) * n);
	visit = (int**)malloc(sizeof(int*) * n);
	way = (pos*)malloc(sizeof(pos) * (n*m));

	for (int i = 0; i < n; i++) {
		maze[i] = (int*)malloc(sizeof(int) * m);
		visit[i] = (int*)malloc(sizeof(int) * m);
		for (int  j = 0; j < m; j++){
			fscanf(fp, "%d", &maze[i][j]);
			visit[i][j] = 0;
		}
	}

	printf("미로정보\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	fix();

	if (way[top].x == n - 1 && way[top].y == m - 1) {
		printf("미로 탈출 경로\n");
		printf("row col\n");
		for (int i = 0; i <= top; i++)
		{
			printf("%2d  %2d\n", way[i].x, way[i].y);
		}
	}
	else printf("no way\n");
}