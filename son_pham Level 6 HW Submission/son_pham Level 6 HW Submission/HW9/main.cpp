/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Main file that test the implementations of the stacks
*/

#include "Stack.h"
#include <iostream>

int main() {
  Stack stack(5);

  try {
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Push(40);
    stack.Push(50);
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  try {
    while (true) {
      std::cout << "Popped: " << stack.Pop() << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}