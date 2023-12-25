#include "Counter.h"
#include "Observer.h"

int Counter::getCounter() const { return counterValue; }

void Counter::increaseCounter() {
  counterValue++;
  notifyObservers();
}

void Counter::decreaseCounter() {
  counterValue--;
  notifyObservers();
}
