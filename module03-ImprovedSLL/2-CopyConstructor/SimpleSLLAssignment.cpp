#include <cstdlib>
#include <doctest.h>
#include <iostream>
#include "../../module02-SimpleSLL/1-SimpleSLL/SimpleSLL.hpp"

int main() {
  SimpleSLL<int> list1;
  for(int i = 0; i < 10; i++) {
    list1.add(i);
  }
  std::cout << "List 1: ";
  list1.print();
  std::cout << std::endl;

  SimpleSLL<int> list2;
  for(int i = 10; i < 20; i++) {
    list2.add(i);
  }
  std::cout << "List 2: ";
  list2.print();
  std::cout << std::endl;

  list1 = list2;
  std::cout << "List 1: ";
  list1.print();
  std::cout << std::endl;
  
   for(int i = 0; i < 10; i++) {
    list2.set(i, 10 - i);
  }

  std::cout << "List 1 after List 2 is changed: " << std::endl;
  list1.print();
  list2.remove(0);
  std::cout << "List 1 after List 2 element removed: " << std::endl;
  list1.print();
  std::cout << "List 1 size: " << list1.size() << std::endl;
  std::cout << "List 2: ";
  list2.print();

  return EXIT_SUCCESS;
}