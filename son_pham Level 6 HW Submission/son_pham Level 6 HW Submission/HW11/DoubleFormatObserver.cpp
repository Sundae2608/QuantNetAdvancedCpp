/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Double Format Observer
*/

#include "DoubleFormatObserver.h"

void DoubleFormatObserver::update(Subject *subject) {
  Counter *counter = static_cast<Counter *>(subject);
  if (counter != nullptr) {
    std::cout << "Double Format Observer: " << std::fixed
              << std::setprecision(2)
              << static_cast<double>(counter->getCounter()) << std::endl;
  }
}