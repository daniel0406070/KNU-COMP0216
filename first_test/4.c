#include <stdio.h>  
#include <ctype.h>

int main(){
    printf("문자열 입력 : ");
    char str[100];
    gets(str);

    printf("자음만 대문자로 변환 결과 : ");

    for (int i=0; str[i]!='\0'; i++){
        if (str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u'){
            printf("%c", str[i]);
        }
        else{
            printf("%c", toupper(str[i]));
        }
    }
}