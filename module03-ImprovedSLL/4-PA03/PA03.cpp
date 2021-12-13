#include <cstdlib>
#include <doctest.h>
#include <iostream>
#include "SLL.hpp"

int main() {
    SLL<int> list;

    std::cout << "Initial list: " << list << std::endl;

    std::cout << "Adding via +=...";
    for(int i = 1; i <= 10; i++) {
        list += i;
    }
    std::cout << "done." << std::endl;
    std::cout << "List contents: " << list << std::endl;

    std::cout << "Removing 5 via -=...";
    list -= 5;
    std::cout << "done." << std::endl;
    std::cout << "List contents: " << list << std::endl;

    std::cout << "Changing via [ ]...";
    for(int i = 0; i < 9; i++) {
        list[i] *= 2;
    }
    std::cout << "done." << std::endl;
    std::cout << "List contents: " << list << std::endl;

    return EXIT_SUCCESS;
}