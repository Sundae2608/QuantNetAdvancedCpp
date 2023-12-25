/*
* Advanced C++ and Modern Design
* Level 6 - Homework 9
* Author: Son Pham
* Stack state header
*/

#pragma once

class Stack; // Forward declaration

class StackState {
public:
  virtual void Push(Stack *stack, int element) = 0;
  virtual int Pop(Stack *stack) = 0;
};