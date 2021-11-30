#include<stdio.h>
int increase(int n[]);

int main()
{   
    int n[3] = {1,2,3};
    for(int i =0; i<3; i++)
        printf("%d ",n[i]);

    printf("\n");
    //call array++
    increase(n);
     for(int i =0; i<3; i++)
        printf("%d ",n[i]);
    return 0;
}

int increase(int n[]){   
    for(int i =0; i<3; i++)
        n[i]++;
    return 0;
}