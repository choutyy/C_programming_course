#include<stdio.h>
#define MAX 20

int main(void)
{
    int a[MAX] = {0};
    int i,j,duplicate,value;
    int k = 0;

    printf("Enter 20 integers between 10 and 100\n");
    // get 20 integers from user
    for(i=0; i<MAX; i++)
    {
        scanf("%d", &value);
        duplicate = 0;

        //test if the input is duplicate or not
        for(j=0; j<k; j++)
        {
            if(value == a[j])
            {
                duplicate = 1;
                break;
            } // end if
        }// end for

        //if not duplicate, enter it into array
        if(!duplicate){
        a[k++] = value;
        } // end if
    } // end for loop of inputting 20 integers

    printf("The non-duplicated numbers are:\n");

    for(i=0; a[i]!=0 && i<k; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}