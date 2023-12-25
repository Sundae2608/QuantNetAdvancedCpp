/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Stack Header
*/

#pragma once

class StackState;

class Stack {
private:
  int *elements;
  int currentIndex;
  int stackSize;
  StackState *currentState;
  void Init(int size);

  friend class EmptyState;
  friend class FullState;
  friend class NotFullNotEmptyState;

public:
  Stack();
  Stack(int size);
  void Push(int element);
  int Pop();
  int GetCurrentIndex() const;
  int GetSize() const;
  void ChangeState(StackState *newState);
  ~Stack();
};