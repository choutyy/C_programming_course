#include<stdio.h>
int main() {
  float first, second, temp;
  printf("Enter first number: ");
  scanf("%f", &first);
  printf("Enter second number: ");
  scanf("%f", &second);

  // value of first is assigned to temp
  temp = first;

  // value of second is assigned to first
  first = second;

  // value of temp (initial value of first) is assigned to second
  second = temp;

  // %.2lf displays number up to 2 decimal points
  printf("\nAfter swapping, first number = %.2f\n", first);
  printf("After swapping, second number = %.2f", second);
  return 0;
}