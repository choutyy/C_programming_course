#include<stdio.h>

char str_1[12] = "This is dog"; 
char str_2[15] = {'T','h','i','s',' ','i','s',' ','d','o','g','\0','\0','\0','\0'};


int string_len(char str[]){
    int i=0;
    while(str[i]!='\0')
    i++;
    return i;
}
int main(){
    char str[11] = "This is dog";
    printf("Size of string:%zu\n", sizeof(str));
    printf("length of string:%d", string_len(str));
    return 0;
}