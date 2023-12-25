/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Counter header
*/

#ifndef COUNTER_H
#define COUNTER_H

#include "Subject.h"

class Counter : public Subject {
public:
  Counter();
  int getCounter() const;
  void increaseCounter();
  void decreaseCounter();

private:
  int counterValue;
};

#endif // COUNTER_H