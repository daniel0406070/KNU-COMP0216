#include <stdio.h>

#define ROW 3
#define COL 3

int sumAry2D_f1(int ary[][3], int n, int m){
    int sum=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            sum+=ary[i][j];
        }
    }
    return sum;
}

int sumAry2D_f2(int (*ary)[3], int n){
    int sum=0;
    int m=sizeof(ary[0])/sizeof(int);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            sum+=ary[i][j];
        }
    }
    return sum;
}

int sumAry2D_f3(int (*ary)[3]){
    int sum=0;
    int n=3; // 포인터로 넘겨받은 배열은 크기를 알 수 없습니다.
    int m=sizeof(ary[0])/sizeof(int);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            sum+=ary[i][j];
        }
    }
    return sum;
}

int main(){
    int ary2D[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, ROW, COL));
    printf("sumAry2D_f2() %d\n\n", sumAry2D_f2(ary2D, ROW));
    printf("sumAry2D_f3() %d\n\n", sumAry2D_f3(ary2D));
}