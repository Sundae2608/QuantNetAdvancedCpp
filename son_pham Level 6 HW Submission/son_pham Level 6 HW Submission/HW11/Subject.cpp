/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Subject
*/

#include <algorithm>

#include "Subject.h"

void Subject::attach(Observer *observer) { observers.push_back(observer); }

void Subject::detach(Observer *observer) {
  // Find the observer in the vector and remove it
  auto it = std::find(observers.begin(), observers.end(), observer);
  if (it != observers.end()) {
    observers.erase(it);
  }
}

void Subject::notify() {
  for (Observer *observer : observers) {
    observer->update(this);
  }
}
