/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Observer header
*/

#ifndef OBSERVER_H
#define OBSERVER_H

class Subject; // Forward declaration

class Observer {
public:
  virtual ~Observer() =
      default; // Add a virtual destructor. This allows dynamic_cast to work
  virtual void update(Subject *subject) = 0;
};

#endif // OBSERVER_H