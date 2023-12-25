/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Main file testing implementations
*/

#include "Counter.h"
#include "DoubleFormatObserver.h"
#include "LongFormatObserver.h"

int main() {
  Counter counter;

  LongFormatObserver longObserver;
  DoubleFormatObserver doubleObserver;

  std::cout << "Attach Long Format Observer" << std::endl;
  counter.attach(&longObserver);
  std::cout << "Attach Double Format Observer" << std::endl;
  counter.attach(&doubleObserver);

  counter.increaseCounter();
  counter.increaseCounter();

  // Detach the LongFormatObserver
  std::cout << "Detach Long Format Observer" << std::endl;
  counter.detach(&longObserver);

  counter.increaseCounter();
  counter.decreaseCounter();

  return 0;
}
