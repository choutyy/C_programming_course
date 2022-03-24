#include<stdio.h>
int f();  // function declaration

int i = 5;


int main(){
    printf("i=%d\n",i);
    //int i = 6;
    i = i+1;
    f();
    printf("i=%d\n",i);
    return 0;
}

int f(){
    i = i+1;
    printf("i=%d\n",i);
    return 0;
}
