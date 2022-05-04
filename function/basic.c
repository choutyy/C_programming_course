#include<stdio.h>
int f(int);
int i = 10;

int main(){
    printf("i=%d\n",i);
    int i = 7;
    printf("i=%d\n",i);
    printf("i=%d\n",f(i));
    {
        int i = 8;
        printf("i=%d\n",i);
        printf("i=%d\n",f(i));
    }
    return 0;
}

int f(int i){
    return i+3;
}