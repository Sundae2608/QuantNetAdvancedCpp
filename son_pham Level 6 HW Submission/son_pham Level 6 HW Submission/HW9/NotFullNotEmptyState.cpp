/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Not Full Not Empty State
*/

#include "NotFullNotEmptyState.h"
#include "EmptyState.h"
#include "FullState.h"

NotFullNotEmptyState::NotFullNotEmptyState() {}

NotFullNotEmptyState *NotFullNotEmptyState::GetInstance() {
  static NotFullNotEmptyState instance;
  return &instance;
}

void NotFullNotEmptyState::Push(Stack *stack, int element) {
  stack->elements[stack->currentIndex] = element;
  stack->currentIndex++;
  if (stack->currentIndex == stack->GetSize() - 1) {
    stack->ChangeState(FullState::GetInstance());
  }
}

int NotFullNotEmptyState::Pop(Stack *stack) {
  if (stack->currentIndex == 1) {
    stack->ChangeState(EmptyState::GetInstance());
  }
  stack->currentIndex--;
  return stack->elements[stack->currentIndex];
}