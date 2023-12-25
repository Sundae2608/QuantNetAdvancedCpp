/*
* Advanced C++ and Modern Design
* Level 6 - Homework 12
* Author: Son Pham
* Counter
*/

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <vector>

class Observer; // Forward declaration

class Observable {
public:
  void addObserver(Observer *observer);
  void deleteObserver(Observer *observer);
  void notifyObservers();

private:
  std::vector<Observer *> observers;
};

#endif // OBSERVABLE_H