/*
* Advanced C++ and Modern Design
* Level 6 - Homework 11
* Author: Son Pham
* Long Format Observer header
*/

#ifndef LONGFORMATOBSERVER_H
#define LONGFORMATOBSERVER_H

#include "Counter.h"
#include "Observer.h"
#include <iostream>

class LongFormatObserver : public Observer {
public:
  void update(Subject *subject) override;
};

#endif // LONGFORMATOBSERVER_H