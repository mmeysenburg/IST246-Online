#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include "../2-Stack/Stack.hpp"

/**
 * Main program for the Doane CMP 246 Module 5 RPN calculator.
 */
int main() {
    
    // welcome prompt
    std::cout << "Welcome to the Doane RPN Calculator!" << std::endl;
    std::cout << "Please enter an expression in postfix, EOF to quit." 
        << std::endl;
    
    // prepare stack
    Stack<double> stack;

    // read string tokens until there is nothing more to read    
    std::string token;
    double a, b;
    while(std::cin >> token) {
        if(token == "E") {
            // print result of expression
            std::cout << ">> " << stack.pop() << std::endl;
            stack.clear();
        } else if(token == "+") {
            // addition
            b = stack.pop();
            a = stack.pop();
            stack.push(a + b);
        } else if(token == "-") {
            // subtraction
            b = stack.pop();
            a = stack.pop();
            stack.push(a - b);
        } else if(token == "*") {
            // multiplication
            b = stack.pop();
            a = stack.pop();
            stack.push(a * b);
        } else if(token == "/") {
            // division
            b = stack.pop();
            a = stack.pop();
            stack.push(a / b);
        } else {
            // numeric entry 
            stack.push(atof(token.c_str()));
        }
    }
    
    // good bye prompt
    std::cout << "Good bye!" << std::endl;
    
    return EXIT_SUCCESS;
}