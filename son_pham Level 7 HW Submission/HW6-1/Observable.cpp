#include "Observable.h"

void Observable::addObserver(std::function<void(Observable *)> observer) {
  observers.push_back(observer);
}

void Observable::deleteObservers() { observers.clear(); }

void Observable::notifyObservers() {
  for (auto &observer : observers) {
    observer(this);
  }
}