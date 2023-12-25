#include "Counter.h"
#include "Observable.h"

#include <functional>
#include <iomanip>
#include <iostream>

int main() {
  Counter counter;

  int longFormatObserverId = counter.addObserver([&counter]() {
    std::cout << "Long Format Observer: " << counter.getCounter() << std::endl;
  });

  int doubleFormatObserverId = counter.addObserver([&counter]() {
    std::cout << "Double Format Observer: " << std::fixed
              << std::setprecision(2)
              << static_cast<double>(counter.getCounter()) << std::endl;
  });

  counter.increaseCounter();
  counter.increaseCounter();

  std::cout << "Removing observer with ID: " << longFormatObserverId
            << std::endl;
  counter.deleteObserver(longFormatObserverId);

  counter.decreaseCounter();

  return 0;
}