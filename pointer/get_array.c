#include<stdio.h>
int increase(int n[]);
/*
int main()
{   
    int n[9] = {1,2,3,4,5,6,7,8,9};
    int *nptr;
    for(nptr = n; nptr != &n[9]; nptr++)
        printf("%d ",*nptr);
    return 0;
}
*/

int main()
{   
    int n[9] = {1,2,3,4,5,6,7,8,9};
    int *nptr;
    nptr = n;
    while(nptr != &n[9])  // n+9 == &n[0+9]
        printf("%d ",*nptr++);
    return 0;
}


