#ifndef COUNTER_H
#define COUNTER_H

#include <deque>

#include "Observable.h"

class Counter : public Observable<std::deque> {
public:
  int getCounter() const;
  void increaseCounter();
  void decreaseCounter();

private:
  int counterValue;
};

#endif // COUNTER_H