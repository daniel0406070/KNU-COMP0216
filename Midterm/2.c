#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
	FILE* fp1 = fopen("input2-1.txt", "r");
	FILE* fp2 = fopen("input2-2.txt", "r");

		int n1,r1,c1,n2,r2,c2;
	fscanf(fp1, "%d %d %d", &r1, &c1, &n1);
	fscanf(fp2, "%d %d %d", &r2, &c2, &n2);

	int** a1 = (int**)malloc(sizeof(int*) * n1);
	int** a2 = (int**)malloc(sizeof(int*) * n2);


	for (int i = 0; i < n1; i++) {
		a1[i] = (int*)malloc(sizeof(int) * 3);
		fscanf(fp1, "%d %d %d", &a1[i][0], &a1[i][1], &a1[i][2]);
	}

	for (int i = 0; i < n2; i++) {
		a2[i] = (int*)malloc(sizeof(int) * 3);
		fscanf(fp2, "%d %d %d", &a2[i][0], &a2[i][1], &a2[i][2]);
	}

	printf("입력 sparse matrix\n");
	printf("%3d, %3d, %3d\n", r1, c1, n1);
	for (int i = 0; i < n1; i++) {
		printf("%3d, %3d, %3d\n", a1[i][0], a1[i][1], a1[i][2]);
	}
	printf("\n\n");

	printf("입력 sparse matrix\n");
	printf("%3d, %3d, %3d\n", r2, c2, n2);
	for (int i = 0; i < n2; i++) {
		printf("%3d, %3d, %3d\n", a2[i][0], a2[i][1], a2[i][2]);
	}

	printf("\n\n");

	int** ans = (int**)malloc(sizeof(int*) * (n1 + n2));
	for (int i = 0; i < (n1 + n2); i++) {
		ans[i] = (int*)malloc(sizeof(int) * 3);
	}

	int idx1 = 0, idx2 = 0, idx_ans = 0;
	while (idx1 < n1 && idx2 < n2) {
		if (a1[idx1][0] == a2[idx2][0]) {
			if (a1[idx1][1] == a2[idx2][1]) {
				ans[idx_ans][0] = a1[idx1][0];
				ans[idx_ans][1] = a1[idx1][1];
				ans[idx_ans][2] = a1[idx1][2] + a2[idx2][2];
				idx_ans++;
				idx1++;
				idx2++;
			}
			else if (a1[idx1][1] < a2[idx2][1]) {
				ans[idx_ans][0] = a1[idx1][0];
				ans[idx_ans][1] = a1[idx1][1];
				ans[idx_ans][2] = a1[idx1][2];
				idx_ans++;
				idx1++;
			}
			else {
				ans[idx_ans][0] = a2[idx2][0];
				ans[idx_ans][1] = a2[idx2][1];
				ans[idx_ans][2] = a2[idx2][2];
				idx_ans++;
				idx2++;
			}
		}
		else if (a1[idx1][0] < a2[idx2][0]) {
			ans[idx_ans][0] = a1[idx1][0];
			ans[idx_ans][1] = a1[idx1][1];
			ans[idx_ans][2] = a1[idx1][2];
			idx_ans++;
			idx1++;
		}
		else {
			ans[idx_ans][0] = a2[idx2][0];
			ans[idx_ans][1] = a2[idx2][1];
			ans[idx_ans][2] = a2[idx2][2];
			idx_ans++;
			idx2++;
		}
	}

	while (idx1 < n1) {
		ans[idx_ans][0] = a1[idx1][0];
		ans[idx_ans][1] = a1[idx1][1];
		ans[idx_ans][2] = a1[idx1][2];
		idx_ans++;
		idx1++;
	}

	while (idx2 < n2) {
		ans[idx_ans][0] = a2[idx2][0];
		ans[idx_ans][1] = a2[idx2][1];
		ans[idx_ans][2] = a2[idx2][2];
		idx_ans++;
		idx2++;
	}

	int r3, c3, n3;
	r3 = r1 > r2 ? r1 : r2;
	c3 = c1 > c2 ? c1 : c2;
	n3 = idx_ans;


	printf("결과 sparse matrix\n");
	printf("%3d, %3d, %3d\n", r3, c3, n3);
	for (int i = 0; i < idx_ans; i++) {
		printf("%3d, %3d, %3d\n", ans[i][0], ans[i][1], ans[i][2]);
	}


	fclose(fp1);
	fclose(fp2);
}