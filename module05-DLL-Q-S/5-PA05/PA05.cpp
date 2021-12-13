#include <cstdlib>
#include <iostream>
#include "DLL.hpp"

int main() {
    DLL<char> list1;
    for(char c = 'a'; c <= 'e'; c++) {
        list1.addLast(c);
    }

    DLL<char> list2 = list1.reverse();

    std::cout << "Original list: " << list1 << std::endl;
    std::cout << "Reversed list: " << list2 << std::endl;

    return EXIT_SUCCESS;
}