/*
* Advanced C++ and Modern Design
* Level 6 - Homework 12
* Author: Son Pham
* Counter
*/

#include <iostream>

#include "Counter.h"

Counter::Counter() : counterValue(0) {}

int Counter::getCounter() const { return counterValue; }

void Counter::increaseCounter() {
  counterValue++;
  notifyObservers();
}

void Counter::decreaseCounter() {
  counterValue--;
  notifyObservers();
}

void Counter::update(Observable *observable) {
  if (observable == this) {
    std::cout << "Counter is observing itself!" << std::endl;
  }
  // Handle updates from other observables if needed
}