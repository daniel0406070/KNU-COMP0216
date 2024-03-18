#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int find_start(char *str, char *pattern){
    int i, j;

    int len_str = strlen(str);
    int len_pattern = strlen(pattern);

    for(i = 0; i < len_str - len_pattern; i++){
        for(j = len_pattern-1; j >= 0; j--){
            if(str[i+j] != pattern[j]){
                break;
            }
        }
        if(j == -1){
            return i;
        }
    }
    return -1;
}



int main(){
    char str[MAX];
    char pattern[MAX];

    printf("문자열을 입력하세오: ");
    fgets(str, MAX, stdin);
    str[strlen(str)-1] = '\0';

    printf("비교할 문자열을 입력하세요: ");
    fgets(pattern, MAX, stdin);
    pattern[strlen(pattern)-1] = '\0';

    int start = find_start(str, pattern);
    if(start == -1)
        printf("찾을 수 없습니다.\n");
    else
        printf("문자열 %d 번째부터 패턴이 시작됨..", start);
}