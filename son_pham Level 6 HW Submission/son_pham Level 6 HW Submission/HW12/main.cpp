/*
* Advanced C++ and Modern Design
* Level 6 - Homework 12
* Author: Son Pham
* Main file testing implementation
*/

#include "Counter.h"
#include <iostream>

int main() {
  Counter counter;

  counter.addObserver(&counter);

  counter.increaseCounter();
  counter.decreaseCounter();

  return 0;
}