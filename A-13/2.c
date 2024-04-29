#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree{
    short int leftThread;
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;
} threadedTree;

threadedPointer insucc(threadedPointer tree){
    threadedPointer temp;
    temp = tree->rightChild;
    if(!tree->rightThread){
        while(!temp->leftThread) temp = temp->leftChild;
    }
    return temp;
}

void tinorder(threadedPointer tree){
    threadedPointer temp = tree;
    for(;;){
        printf("%p(%d, %p, %c, %d, %p)\n", temp, temp->leftThread, temp->leftChild, temp->data, temp->rightThread, temp->rightChild);
        temp = insucc(temp);
        if(temp == tree) break;
    }
    printf("\n");
}

int main(){
    threadedPointer root;
    threadedPointer tmp[10];
    for(int i=0;i<10;i++){
        tmp[i] = (threadedPointer)malloc(sizeof(threadedTree));
        tmp[i]->leftChild = NULL;
        tmp[i]->rightChild = NULL;
        tmp[i]->leftThread = 0;
        tmp[i]->rightThread = 0;
    }

    root = tmp[0];
    root->data = ' ';
    root->leftChild = tmp[1];
    root->rightChild = root;
    tmp[1]->data = 'A';
    tmp[1]->leftChild = tmp[2];
    tmp[1]->rightChild = tmp[3];
    tmp[2]->data = 'B';
    tmp[2]->leftChild = tmp[4];
    tmp[2]->rightChild = tmp[5];
    tmp[3]->data = 'C';
    tmp[3]->leftChild = tmp[6];
    tmp[3]->rightChild = tmp[7];
    tmp[4]->data = 'D';
    tmp[4]->leftChild = tmp[8];
    tmp[4]->rightChild = tmp[9];
    tmp[5]->data = 'E';
    tmp[5]->leftChild = tmp[2];
    tmp[5]->rightChild = tmp[1];
    tmp[5]->leftThread = 1;
    tmp[5]->rightThread = 1;
    tmp[6]->data = 'F';
    tmp[6]->leftChild = tmp[1];
    tmp[6]->rightChild = tmp[3];
    tmp[6]->leftThread = 1;
    tmp[6]->rightThread = 1;
    tmp[7]->data = 'G';
    tmp[7]->leftChild = tmp[3];
    tmp[7]->rightChild = root;
    tmp[7]->leftThread = 1;
    tmp[7]->rightThread = 1;
    tmp[8]->data = 'H';
    tmp[8]->leftChild = root;
    tmp[8]->rightChild = tmp[4];
    tmp[8]->leftThread = 1;
    tmp[8]->rightThread = 1;
    tmp[9]->data = 'I';
    tmp[9]->leftChild = tmp[4];
    tmp[9]->rightChild = tmp[2];
    tmp[9]->leftThread = 1;
    tmp[9]->rightThread = 1;



    tinorder(root);
    return 0;
    
}