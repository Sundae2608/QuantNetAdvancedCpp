/*
* Advanced C++ and Modern Design
* Level 6 - Homework 12
* Author: Son Pham
* Observer Header
*/

#ifndef OBSERVER_H
#define OBSERVER_H

class Observable; // Forward declaration

class Observer {
public:
  virtual void update(Observable *observable) = 0;
};

#endif // OBSERVER_H