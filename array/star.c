#include <stdio.h>
main()
{
    int side ;
    printf("Please enter the side:\n");
    scanf("%d", &side);
    // plot reverse triangle
    for(int i=side; i>0; i--)
    {
        for(int j=1; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}