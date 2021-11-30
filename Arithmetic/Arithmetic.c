#include<stdio.h>
int main()
{
    int a, b, c;
  // Ask the user to enter the first integer
  printf("Enter the first integer:\n");
  scanf("%d", &a);
  // Ask the user to enter second and third integer
  printf("Enter the second integer:\n");
  scanf("%d", &b);
   // Ask the user to enter second and third integer
  printf("Enter the third integer:\n");
  scanf("%d", &c);
  
  // Do arithmetric and print 
  // print the sum of two inputs
  double average = (a+b+c)/3.;
  printf("Average = %f\n", average);
  
  // Do arithmetric and print 
  // print the sum of two inputs
  printf("First integer plus second one = %d\n", a + b );

    // print the difference of two inputs
  printf("Subtract second integer from first one = %d\n", a - b );

    // print the multiplication of two inputs
  printf("First integer multiply second one = %d\n", a*b );

    // print the / of two inputs
  printf("First integer divided by second one = %d\n", a / b );

    // print the % of two inputs
  printf("The remainder when first one divided by second one = %d\n", a % b );
  return 0;
}