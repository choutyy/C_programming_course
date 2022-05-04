#include<stdio.h>
int increase(int);

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
    // return ++n;
    return n++; 
}