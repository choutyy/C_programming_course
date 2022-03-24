#include<stdio.h>
int main() 
 {
    int num1,num2;
    printf("Please enter 2 numbers and I'll tell you which one is larger:\n");
    scanf("%d%d",&num1,&num2);
    
    // check the three sides are equal or not 
    if (num1 < num2){
        printf("The second one %d is larger\n", num2);
    } else if (num1 > num2){
        printf("The first one %d is larger\n", num1);
    } else {
        printf("Looks like they are the same\n");
        }
    return 0; 
 }