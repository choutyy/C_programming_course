#include<stdio.h>
int upstairs(int num);

int main(){
    int i; // integer
    printf("Please enter the level number (must>0)\n");
    scanf("%d", &i);
    printf("Total number of ways to reach level %d = %d.", i, upstairs(i));
    return 0;
}

int upstairs(int num){
    // base case 
    if (num <= 2)
    return num;
    else
    return upstairs(num-2) + upstairs(num-1);
}