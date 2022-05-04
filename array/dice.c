#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    srand(time(0));
    int dice_count[6] = {0};
    for(int j = 1; j<=6000; j++){
        int dice = rand() % 6 + 1;
        dice_count[dice-1]++;
        /*for(int i = 0; i<=5; i++){
            if(dice == i+1)
                dice_count[i]++;
                continue;
        }
        */
    }
    for(int k = 0; k<=5; k++){
        printf("Number %d shows %d times\n", k+1, dice_count[k]);
    }
    return 0;
}