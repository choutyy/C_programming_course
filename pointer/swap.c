#include<stdio.h>
void compare(int, int);
void swap(int *,int * );

int main(){
    int a = 99;
    int b = 88;
    compare(a,b);

    printf("a = %d\n", a);
    printf("b = %d\n", b);
    return 0;
}
void compare(int a, int b){
    if (a>b){
    swap(&a,&b);
    }
}

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}