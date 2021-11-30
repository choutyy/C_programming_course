#include<stdio.h>
int array_length(int array[]);

int main(){
    int a[] = {1,2,3,-1};
    printf("Length of a: %d\n", array_length(a));
    return 0;
}

int array_length(int array[]){

    int i = 0;
    while(array[i]!=-1){
        i++;
    }
    return i;
}