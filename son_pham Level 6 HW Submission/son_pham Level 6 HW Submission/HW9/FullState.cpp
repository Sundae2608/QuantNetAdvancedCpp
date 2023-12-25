/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Full State
*/

#include "FullState.h"
#include "EmptyState.h"
#include "NotFullNotEmptyState.h"

FullState::FullState() {}

FullState *FullState::GetInstance() {
  static FullState instance;
  return &instance;
}

void FullState::Push(Stack *stack, int element) {
  throw std::runtime_error("Cannot push onto a full stack.");
}

int FullState::Pop(Stack *stack) {
  if (stack->currentIndex == 1) {
    stack->ChangeState(EmptyState::GetInstance());
  } else {
    stack->ChangeState(NotFullNotEmptyState::GetInstance());
  }
  stack->currentIndex--;
  return stack->elements[stack->currentIndex];
}