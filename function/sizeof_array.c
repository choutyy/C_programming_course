#include<stdio.h>
int function(int array[]);

int main(){
    int a[3] = {1,2,3};
    function(a);
    return 0;
}

int function(int array[]){
    printf("Size of integer: %zu\n", sizeof(int));
    printf("Size of a[i]: %zu\n", sizeof(array[0]));
    printf("Size of a: %zu\n", sizeof(array));
    printf("Length of a: %zu\n", sizeof(array)/sizeof(array[0]));
    return 0;
}