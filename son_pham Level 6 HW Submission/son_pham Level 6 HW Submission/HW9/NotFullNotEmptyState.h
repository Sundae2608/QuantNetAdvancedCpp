/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Not Full Not Empty State header
*/

#pragma once
#include "Stack.h"
#include "StackState.h"

#include <stdexcept>

class NotFullNotEmptyState : public StackState {
private:
  NotFullNotEmptyState();

public:
  static NotFullNotEmptyState *GetInstance();
  void Push(Stack *stack, int element) override;
  int Pop(Stack *stack) override;
};