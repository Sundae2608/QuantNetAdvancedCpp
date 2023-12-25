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