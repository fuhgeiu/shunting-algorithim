#include <iostream>
#include "class.h"

int main () {


        Calculator calculator;

        // Prints out the number 7
        std::cout << calculator.evaluate("2 + 5");

        // Prints out the number 33
        std::cout << calculator.evaluate("3 + 6 * 5");

        // Prints out the number 20
        std::cout << calculator.evaluate("4 * (2 + 3)");

        // Prints out the number 2
        std::cout << calculator.evaluate("(7 + 9) / 8");

        // Prints out number 4
        std::cout << calculator.evaluate("9 - 5");




}