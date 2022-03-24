#include <stdio.h>
int max3(int [3]);
int max5(int [5]);
int maxarray(int [], int );

int main()
{
    int a[3] = {5,7,9};
    printf("Max: %d\n", max3(a)); // return the maximum one 
    printf("Max: %d\n", maxarray(a,3));
    int b[5] = {2,4,6,8,10};
    printf("Max: %d\n", max5(b)); // return the maximum one 
    printf("Max: %d\n", maxarray(b,5));

    return 0;
}

int max3(int *array)
{
    int max = array[0];  // assume the first one is maximum
    for(int i=1; i<3; i++){
        if(array[i]>max) //if larger than the assume one, change it 
        max = array[i];
    }
    return max;
}

int max5(int array[5])
{
    int max = array[0];  // assume the first one is maximum
    for(int i=1; i<5; i++){
        if(array[i]>max) //if larger than the assume one, change it 
        max = array[i];
    }
    return max;
}

int maxarray(int array[], int number)
{
    int max = array[0];
    for(int i=1; i<number; i++){
        if(array[i]>max)
        max = array[i];
    }
    return max;
}