/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Double Format Observer
*/

#include "LongFormatObserver.h"

void LongFormatObserver::update(Subject *subject) {
  Counter *counter = static_cast<Counter *>(subject);
  if (counter != nullptr) {
    std::cout << "Long Format Observer: " << counter->getCounter() << std::endl;
  }
}