
#include <iostream> // allows program to perform input and output 
 
 int main() 
{ 
     int number1; // first integer to add 
 
    std::cout << "Enter first integer: "; // prompt user for data 
    std::cin >> number1; // read first integer from user into number1 

    int number2; // second integer to add 
    int sum; // sum of number1 and number2 

    std::cout << "Enter second integer: "; // prompt user for data 
    std::cin >> number2; // read second integer from user into number2 
    sum = number1 + number2; // add the numbers; store result in sum 
    std::cout << "Sum is " << sum << std::endl; // display sum; end line 
 
    return 0; // indicate that program ended successfully 
} // end function main 
