#include <stdio.h>

int main()
{
  int a, b, c;
  // Ask the user to enter the first integer
  printf("Enter the first integer:\n");
  scanf("%d", &a);
  // Ask the user to enter second and third integer
  printf("Enter the second integer:\n");
  scanf("%d", &b);

  printf("Enter the third integer:\n");
  scanf("%d", &c);

  // print the sum of three inputs
  printf("The sum of three inputs:%d\n", a + b + c);
  return 0;
}
