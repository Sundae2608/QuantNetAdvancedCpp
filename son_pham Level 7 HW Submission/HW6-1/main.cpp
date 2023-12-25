#include "Counter.h"
#include "Observable.h"

#include <functional>
#include <iomanip>
#include <iostream>

void longFormatObserver(Observable *observable) {
  Counter *counter = dynamic_cast<Counter *>(observable);
  if (counter) {
    std::cout << "Long Format Observer: " << counter->getCounter() << std::endl;
  }
}

void doubleFormatObserver(Observable *observable) {
  Counter *counter = dynamic_cast<Counter *>(observable);
  if (counter) {
    std::cout << "Double Format Observer: " << std::fixed
              << std::setprecision(2)
              << static_cast<double>(counter->getCounter()) << std::endl;
  }
}

int main() {
  Counter counter;

  // Adding observer functions
  counter.addObserver(longFormatObserver);
  counter.addObserver(doubleFormatObserver);

  counter.increaseCounter();
  counter.increaseCounter();
  counter.decreaseCounter();

  return 0;
}