/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Double Format Observer header
*/

#ifndef DOUBLEFORMATOBSERVER_H
#define DOUBLEFORMATOBSERVER_H

#include "Counter.h"
#include "Observer.h"
#include <iomanip>
#include <iostream>

class DoubleFormatObserver : public Observer {
public:
  void update(Subject *subject) override;
};

#endif // DOUBLEFORMATOBSERVER_H