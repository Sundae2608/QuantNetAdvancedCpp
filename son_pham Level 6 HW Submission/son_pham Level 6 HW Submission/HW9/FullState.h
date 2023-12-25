/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Full State header
*/

#pragma once

#include "Stack.h"
#include "StackState.h"

class FullState : public StackState {
private:
  FullState();

public:
  static FullState *GetInstance();
  void Push(Stack *stack, int element) override;
  int Pop(Stack *stack) override;
};