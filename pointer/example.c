#include <stdio.h>
/* swap */
void swap(int *a, int *b)
{
int temp;
temp = *a;
printf("size of temp = %d\n", sizeof(temp));
printf("value of temp = %d\n",temp);
printf("value of *a = %d\n",*a);
*a = *b;
*b = temp;
}
/* main */
int main(void)
{
int i, j;
scanf("%d", &i);
scanf("%d", &j);
printf("value of &i = %d\n",&i);
printf("value of &j = %d\n",&j);
swap(&i, &j);
printf("i = %d, j = %d\n", i, j);
return 0;
}


