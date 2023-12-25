/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Empty State
*/

#include "EmptyState.h"
#include "NotFullNotEmptyState.h"

#include <stdexcept>

EmptyState::EmptyState() {}

EmptyState *EmptyState::GetInstance() {
  static EmptyState instance;
  return &instance;
}

void EmptyState::Push(Stack *stack, int element) {
  stack->elements[stack->currentIndex] = element;
  stack->currentIndex++;
  stack->ChangeState(NotFullNotEmptyState::GetInstance());
}

int EmptyState::Pop(Stack *stack) {
  throw std::runtime_error("Cannot pop from an empty stack.");
}