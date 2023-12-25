/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Stack
*/

#include "Stack.h"
#include "EmptyState.h"
#include "StackState.h"

void Stack::Init(int size) {
  if (size < 1)
    size = 1;
  elements = new int[size];
  currentIndex = 0;
  currentState = EmptyState::GetInstance();
  stackSize = size;
}

Stack::Stack() { Init(1); }

Stack::Stack(int size) { Init(size); }

void Stack::Push(int element) { currentState->Push(this, element); }

int Stack::Pop() { return currentState->Pop(this); }

int Stack::GetCurrentIndex() const { return currentIndex; }

int Stack::GetSize() const { return stackSize; }

void Stack::ChangeState(StackState *newState) { currentState = newState; }

Stack::~Stack() { delete[] elements; }