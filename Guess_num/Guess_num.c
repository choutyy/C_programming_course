#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    // Initialized variables
   int guess;
   int play_option = 0;
   int guess_time = 1;
   srand(time(NULL));
   int my_num = rand() % 101;
   // start game
   printf("I have a number between 1 and 100\nCan you guess my number?\nPlease type your first guess (enter -1 to end):\n");
   scanf("%d", &guess);

   while(guess != -1)
   {
        //printf("my_num = %d",my_num);  
            if(guess < my_num)
            {
                printf("Too low, try again\n");
                guess_time++;
                scanf("%d", &guess);
            }
            else if(guess > my_num)
            {
                printf("Too high, try again\n");
                guess_time++;
                scanf("%d", &guess);
            }
    
            else if(guess = my_num)
            {        
                guess_time++;    
                printf("Excellent! You took %d times to guess my number!\nWould you like to play again? (type 1 to start a new game; -1 to end)", guess_time);
                scanf("%d", &play_option);
                    if(play_option == 1)
                    {
                        printf("I have a number between 1 and 100\nCan you guess my number?\nPlease type your first guess (enter -1 to end):\n");
                        scanf("%d", &guess);
                        my_num = rand() % 101;
                        guess_time = 1;
                        //printf("my_num = %d",my_num);
                    }
                    else if(play_option == -1)
                    {guess = -1;} // break the while
        }
   }
return 0;
}