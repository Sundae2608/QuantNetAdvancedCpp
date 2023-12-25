/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Empty State header
*/

#pragma once

#include "Stack.h"
#include "StackState.h"

class EmptyState : public StackState {
private:
  EmptyState();

public:
  static EmptyState *GetInstance();
  void Push(Stack *stack, int element) override;
  int Pop(Stack *stack) override;
};