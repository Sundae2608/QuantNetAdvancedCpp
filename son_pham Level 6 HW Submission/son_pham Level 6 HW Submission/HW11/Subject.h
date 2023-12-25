/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Subject header
*/

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>

class Subject {
public:
  void attach(Observer *observer);
  void detach(Observer *observer);
  void notify();

private:
  std::vector<Observer *> observers;
};

#endif // SUBJECT_H