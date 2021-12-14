#include<stdio.h>

int main(){
    int home = 4.00; // store value of home 

    int dad = 1; // integer
    int *mom; // pointer

   /* dad = home; // O
    mom = home; // X

    dad = &home; // X
    mom = &home; // O

    home = *dad; // X
    home = *mom; // O

   */

    int *homePtr = &home; // store the memory location(address) of home
    int house = *homePtr; // value of home assigned to house
    int house = *&home;
    house = 10;

    *homePtr = 10; 
    
    printf("%d\n", &home);
    printf("%d\n", homePtr); // value of homePtr
    printf("%p\n", homePtr); // memory address of home 
    return 0;
}