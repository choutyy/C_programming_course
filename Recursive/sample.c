#include<stdio.h>
int f(int num);

int main(){
    int i = 0;
    printf("%d", f(i));
    return 0;
}

int f(int num){
    if (num == 2)
    return num;
    else
    return f(num+1);
}