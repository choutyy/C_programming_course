// use pointer to conduct bubble sort with ascending order
#include<stdio.h>
#define size 10
void printArray(int a[], int i);
void bubblesort(int *a, int i); // only need to replace "int a[]" with "int a*" 

int main(){
    int array[size];
    int i;
    // ask user to input array value 
    printf("enter an 1 by 10 array\n");
    for(i=0; i<size; i++){
        scanf("%d", &array[i]);
    }
    printf("\n");
    printArray(array,i);
    bubblesort(array,i); // Implicit type conversion: array into &array[0]
    printf("\n");
    printArray(array,i);
    return 0;
}

void printArray(int a[], int i){
    for(i=0; i<size; i++){
        printf("%4d", a[i]);
    }
}

void bubblesort(int *a, int i){ // only need to replace "int a[]" with "int a*" 
    int j; // the number of rest elements
    int temp;
    for (i=0; i<size; i++){
        for (j=0; j<i; j++){
            if(a[j]>a[i]){
                temp = a[j];   // a is a pointer, a = &a[0], a[index] = *(a+index)
                a[j] = a[i];
                a[i] = temp;
            }

        }
    }
}
