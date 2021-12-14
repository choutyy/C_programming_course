#include<stdio.h>
int min(int *, int *);

int main(){
    int a = 99;
    int b = 88;
    printf("min = %d", min(&a,&b));
    return 0;
}

int min(int *a, int*b){
    if(*a<*b)
    return *a;
    else
    return *b;
}