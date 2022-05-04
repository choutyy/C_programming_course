#include<stdio.h>
#define arraySize 10

int main(){
    int a[arraySize] = {0};
 
    int key; 
    int index = -1; 

    // create an array 
    for (int i =0; i < arraySize/2; i++){
        a[i] = 2 * i; 
    }

    // ask user to enter integer search key 
    printf("Enter an interger key: \n");
    scanf("%d", &key); 

    // search through array 
    for (int j = 0; j < arraySize; j++){
        if (a[j] == key){
            index = j; 
            printf("Found %d at index %d\n", key, index);
        }
    }

    // print message if not found value 
    if(index == -1) printf("Not found"); 

    return 0;
}