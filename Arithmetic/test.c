#include <stdio.h> 
int main() 
 {
    int score;
    printf("Please enter the score\n");
    scanf("%d",&score);
    printf("Student score = %d\n",score);
    // check pass or not
    if (score >= 60){
       printf("Get the credit!!\n");
    }
    if (score < 60){
       printf("Retake the course!!\n");
   }
    
    return 0; 
 }