#include<stdio.h>
int main() {
  double first, second, third, temp;
  printf("Enter three number: ");
  scanf("%lf%lf%lf", &first, &second, &third);
  printf("Before sorting: %.2f  %.2f  %.2f\n", first, second, third);
  // compare first and second
  if (second<first){
    temp = second; second = first; first = temp;
  }
  // compare first and third
    if (third<first){
    temp = third; third = first; first = temp;
    }
  // compare second and third
    if (third<second){
    temp = third; third = second; second = temp;
    }
  printf("After sorting: %.2f  %.2f  %.2f\n", first, second, third);
  return 0;
}