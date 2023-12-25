/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Shape header
*/

#ifndef SHAPE_H
#define SHAPE_H

#include "ShapeVisitor.h"
#include <iostream>

class Shape {
public:
  virtual ~Shape() {}
  virtual void print(std::ostream &os) const = 0;
  virtual Shape *Clone() const = 0;
  virtual void Accept(ShapeVisitor &shape_visitor) = 0;
};

std::ostream &operator<<(std::ostream &os, const Shape &shp);

#endif // SHAPE_H