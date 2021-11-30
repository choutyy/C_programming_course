#include<stdio.h>
int factorial(int num);

int main(){
    int i; // counter
// Run factorial 11 times and print the result every time.
    for(i=0; i<11; i++)
        printf("%d! = %d\n", i, factorial(i));
    return 0;
}

int factorial(int num){
    // base case 
    if (num <= 1)
    return 1;
    else
    return num*factorial(num-1);
}