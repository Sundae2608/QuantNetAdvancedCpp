/*
* Advanced C++ and Modern Design
* Level 6 - Homework 8
* Author: Son Pham
* Name Decorator
*/

#include "NameDecorator.h"
#include <iostream>

NameDecorator::NameDecorator() : name("") {}

NameDecorator::NameDecorator(Shape *shape, const std::string &name)
    : ShapeDecorator(shape), name(name) {}

std::string NameDecorator::GetName() const { return name; }

void NameDecorator::SetName(const std::string &name) { this->name = name; }

void NameDecorator::print(std::ostream &os) const {
  if (GetShape()) {
    os << *GetShape() << " with name: " << name;
  }
}

Shape *NameDecorator::Clone() const {
  if (GetShape()) {
    return new NameDecorator(GetShape()->Clone(), name);
  }
  return nullptr;
}