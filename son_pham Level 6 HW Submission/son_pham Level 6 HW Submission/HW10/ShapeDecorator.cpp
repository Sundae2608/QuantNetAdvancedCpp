/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Shape Decorator
*/

#include "ShapeDecorator.h"

ShapeDecorator::ShapeDecorator() : decoratedShape(nullptr) {}

ShapeDecorator::ShapeDecorator(Shape *shape) : decoratedShape(shape) {}

Shape *ShapeDecorator::GetShape() const { return decoratedShape; }

void ShapeDecorator::SetShape(Shape *shape) { decoratedShape = shape; }

Shape *ShapeDecorator::Clone() const {
  if (decoratedShape) {
    return decoratedShape->Clone();
  }
  return nullptr;
}

void ShapeDecorator::Accept(ShapeVisitor &visitor) {
  decoratedShape->Accept(visitor);
}