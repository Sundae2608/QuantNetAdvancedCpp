#ifndef COUNTER_H
#define COUNTER_H

#include "Observable.h"

class Counter : public Observable {
public:
  Counter();
  int getCounter() const;
  void increaseCounter();
  void decreaseCounter();

private:
  int counterValue;
};

#endif // COUNTER_H