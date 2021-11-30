#include<stdio.h>
int increase(int n);

int main()
{   
    int n = 1;
    increase(n);
    printf("n = %d \n", n);
    printf("n = %d \n", increase(n));
    return 0;
}

int increase(int n)
{   
    n++;
    return n++;
}