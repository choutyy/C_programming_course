#include<stdio.h>
void increase(int n);

int main(){
    int n=1;
    printf("n = %d\n", n);
    increase(n);
    printf("n = %d\n", n);
    return 0;
}

void increase(int a){
    a = a+1;
}