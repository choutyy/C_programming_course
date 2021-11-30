#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{   
    srand(time(0));
    int i, a[3], b[3];
    for(i=0; i<3; i++){
        a[i] = rand()%10; //create an array
        b[i] = a[i]; //copy each element in an array
        printf("%d ", a[i]);
    }
    for(i=0; i<3; i++){
        printf("%d ", b[i]);
    }
    
    return 0;
}
