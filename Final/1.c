#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nptr;
typedef struct node {
	char data;
	nptr left;
	nptr right;
} node;

nptr root = NULL;

nptr stack[25] = { 0, };
int top = 0;


void insert(char data) {
	nptr tmp = (nptr)malloc(sizeof(node));
	tmp->right = NULL;
	tmp->left = NULL;
	tmp->data = data;
	if (data == '+' || data == '-' || data == '*' || data == '/' || data == '%') {
		tmp->right = stack[--top];
		tmp->left = stack[--top];
	}
	stack[top++] = tmp;
}

void inorder(nptr root, int op) {
	if (root != NULL) {
		inorder(root->left,op);
		if(op==1 && (root->data == '+' || root->data == '-' || root->data == '*' || root->data == '/' || root->data == '%')){
		}
		else if(op == 2 && !(root->data == '+' || root->data == '-' || root->data == '*' || root->data == '/' || root->data == '%')) {
		}
		else printf("[%p, %c. %p] ",root->left, root->data, root->right);
		
		inorder(root->right,op);
	}
}

int main() {
	FILE* fp = fopen("input1.txt", "r");
	
	char tmp;

	printf("input string(postfix expression) : ");
	while (fscanf(fp, "%c", &tmp)!=EOF) {
		printf("%c", tmp);
		insert(tmp);
	}
	printf("\n");

	printf("creating its binary tree\n\n");
	root = stack[top - 1];

	printf("inorder traversal\n");
	inorder(root,0);
	printf("\n\n");

	printf("연산자 노드 출력\n");
	inorder(root, 2);
	printf("\n\n");

	printf("피연산자 노드 출력\n");
	inorder(root, 1);
	printf("\n\n");

}