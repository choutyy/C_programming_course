#include<stdio.h>
int main() 
 {
    int max;
    printf("Enter the max number for the limited range:\n");
    scanf("%d",&max);    
    // check the number
    for(int number = max; number>=1; number--){
        if (number%3==2 && number%5==3 && number%7==2){
                continue;          
        } 
        printf("Number=%4d meet the quiteria\n", number);    
    } //end for 
    
    return 0; 
 }