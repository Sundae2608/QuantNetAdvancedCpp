/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Counter
*/

#include "Counter.h"

Counter::Counter() : counterValue(0) {}

int Counter::getCounter() const { return counterValue; }

void Counter::increaseCounter() {
  counterValue++;
  notify();
}

void Counter::decreaseCounter() {
  counterValue--;
  notify();
}