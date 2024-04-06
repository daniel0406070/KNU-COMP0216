#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node{
    int exponent;
    int coefficient;
    nptr next;
}node;

nptr avail;

void insert(nptr* headptr, node data, char op){
    nptr head = *headptr;
    nptr new_node = (nptr)malloc(sizeof(node));
    *new_node = data;
    new_node->next = new_node;

    if(head == head->next){
        head->next = new_node;
        new_node->next = head;
    }
    else if(op == 'a'){
        new_node->next = head->next;
        head->next = new_node;
    }
    else{
        nptr temp = head;
        while(temp->next != head){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = head;
    }
    
} 

void attach(nptr* headptr, float coefficient, int exponent){
    nptr head = *headptr;

    nptr new_node = (nptr)malloc(sizeof(node));
    new_node->coefficient = coefficient;
    new_node->exponent = exponent;
    new_node->next = new_node;



    if(head->next == head){
        head->next = new_node;
        new_node->next = head;
    }
    else{
        nptr temp = head;
        while(temp->next != head){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = head;
    }

    return;
}

void go_to_avail(nptr* headptr){
    nptr head = *headptr;
    nptr temp = head;

    while(temp->next != head){
        temp = temp->next;
    }    
    temp->next = avail;
    avail = head;

    *headptr = NULL;
}

void print_aviail(){
    nptr temp = avail->next;
    while(temp != NULL){
        printf("(%016o : ", temp);
        printf("%3c",temp->coefficient < 0 ? '\0' : '+');
        printf("%dx^%d", temp->coefficient, temp->exponent);
        printf(": %016o)\n", temp->next);
        temp = temp->next;
    }
}

void delete_all(nptr *head){
    nptr temp = *head;
    while(temp != NULL){
        nptr temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    *head = NULL;
}


nptr polyadd(nptr *aptr, nptr *bptr){
    nptr a = *aptr;
    nptr b = *bptr;
    nptr temp1 = a->next;
    nptr temp2 = b->next;

    nptr c = (nptr)malloc(sizeof(node));
    c->next = c;

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
        if(temp1 == a || temp2 == b) break;
    }

    while(a != temp1){
        attach(&c, temp1->coefficient, temp1->exponent);
        temp1 = temp1->next;
    }

    while(b != temp2){
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
    
        if(temp->next == head) break;
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    avail = (nptr)malloc(sizeof(node));
    avail->next = NULL;

    FILE *fa = fopen("a.txt", "r");
    FILE *fb = fopen("b.txt", "r");

    nptr a = (nptr)malloc(sizeof(node));
    nptr b = (nptr)malloc(sizeof(node));
    nptr c;

    a->next = a;
    b->next = b;

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

    go_to_avail(&a);
    go_to_avail(&b);
    go_to_avail(&c);

    printf("avail = \n");
    print_aviail();
    

    delete_all(&a);

    fclose(fa);
    fclose(fb);
}