#include <stdio.h>
#define ARRAYSIZE 5

int main()
{
    int array [ARRAYSIZE] = {1}; 

    //for(int i=0; i<5; i++)
    //{
    //    scanf("%d", &array[i]);
    //}   
    for(int i=0; i<5; i++)
    {
        printf("%d\n", array[i]);
    }
    printf("%d\n", array[5]);
    return 0;
}