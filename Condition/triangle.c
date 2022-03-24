#include <stdio.h> 
int main() 
 {
    int length1,length2,length3;
    printf("Please enter the 3 lengths of triangle:\n");
    scanf("%d%d%d",&length1,&length2,&length3);
    
    // check the three sides are equal or not 
    if (length1 == length2){
        if (length2 == length3){
        printf("Yes! It's a ragular triangle\n");
        }
        if (length2 != length3){
        printf("No! It's an isosceles triangle\n");
        }
   }
    return 0; 
 }