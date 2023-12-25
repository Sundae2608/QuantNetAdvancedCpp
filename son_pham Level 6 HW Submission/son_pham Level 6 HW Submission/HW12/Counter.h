/*
* Advanced C++ and Modern Design
* Level 6 - Homework 12
* Author: Son Pham
* Counter header
*/

#ifndef COUNTER_H
#define COUNTER_H

#include "Observable.h"
#include "Observer.h"

class Counter : public Observable, public Observer {
public:
  Counter();
  int getCounter() const;

  void increaseCounter();
  void decreaseCounter();

  void update(Observable *observable) override;

private:
  int counterValue;
};

#endif // COUNTER_H