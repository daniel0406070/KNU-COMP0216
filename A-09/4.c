#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int exponent;
    int coefficient;
    nptr next;
}node;

void insert(nptr* headptr, node data, char op){
    nptr head = *headptr;
    nptr new_node = (nptr)malloc(sizeof(node));
    new_node->coefficient = data.coefficient;
    new_node->exponent = data.exponent;
    new_node->next = NULL;

    if(head == NULL){
        *headptr = new_node;
        return;
    }
    else if(op == 'a'){
        new_node->next = head;
        head = new_node;
        *headptr = head;
    }
    else{
        nptr temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = NULL;
    }
    
} 

void attach(nptr* headptr, float coefficient, int exponent){
    nptr head = *headptr;

    nptr new_node = (nptr)malloc(sizeof(node));
    new_node->coefficient = coefficient;
    new_node->exponent = exponent;
    new_node->next = NULL;



    if(head == NULL){
        *headptr = new_node;
    }
    else{
        nptr temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = NULL;
    }

    return;
}


void delete_all(nptr *head){
    nptr temp = *head;
    while(temp->next != NULL){
        nptr temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    *head = NULL;
}


nptr polyadd(nptr *aptr, nptr *bptr){
    nptr a = *aptr;
    nptr b = *bptr;
    nptr temp1 = a;
    nptr temp2 = b;

    nptr c = NULL;

    while(1){
        if(temp1->exponent > temp2->exponent){
            attach(&c, temp1->coefficient, temp1->exponent);
            temp1 = temp1->next;
        }
        else if(temp1->exponent < temp2->exponent){
            attach(&c, temp2->coefficient, temp2->exponent);
            temp2 = temp2->next;
        }
        else{
            int sum = temp1->coefficient + temp2->coefficient;
            if(sum){
                attach(&c, sum, temp1->exponent);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        if(temp1 == NULL || temp2 == NULL) break;
    }

    while(NULL != temp1){
        attach(&c, temp1->coefficient, temp1->exponent);
        temp1 = temp1->next;
    }

    while(NULL != temp2){
        attach(&c, temp2->coefficient, temp2->exponent);
        temp2 = temp2->next;
    }
    

    return c;

}

void printpoly(nptr* headptr){
    nptr head = *headptr;
    nptr temp = *headptr;
    while(1){
        printf("(%016o : ", temp);
        printf("%3c",temp->coefficient < 0 ? '\0' : '+');
        printf("%dx^%d", temp->coefficient, temp->exponent);
        printf(": %016o)\n", temp->next);
    
        if(temp->next == NULL) break;
        temp = temp->next;
    }
    printf("\n");
}

int main(){ 
    FILE *fa = fopen("a.txt", "r");
    FILE *fb = fopen("b.txt", "r");

    nptr a = NULL;
    nptr b = NULL;
    nptr c = NULL;

    char op_a, op_b;
    node temp;
    fscanf(fa, "%c", &op_a);
    fscanf(fb, "%c", &op_b);

    while(fscanf(fa, "%d %d", &temp.coefficient, &temp.exponent) != EOF){
        insert(&a, temp, op_a);
    }

    while(fscanf(fb, "%d %d", &temp.coefficient, &temp.exponent) != EOF){
        insert(&b, temp, op_b);
    }


    printf("A(x) = \n");
    printpoly(&a);
    printf("B(x) = \n");
    printpoly(&b);

    
    c = polyadd(&a, &b);
    printf("A(x)+B(x) = \n");
    printpoly(&c);

    delete_all(&a);
    delete_all(&b);
    delete_all(&c);

    fclose(fa);
    fclose(fb);
}