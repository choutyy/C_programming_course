#include <stdio.h> 
int main() 
 {
  int fahrenheit;
  float celsius;
  for(fahrenheit = 0; fahrenheit <= 212; fahrenheit++)
  {
   celsius = (fahrenheit - 32) * 5.0 / 9.0;
   printf(" \n %10d Fahrenheit = %10.3f Celsius", fahrenheit, celsius);
   printf(" \n %3d Fahrenheit = %.3f Celsius", fahrenheit, celsius);
  }
  return 0; 
 }