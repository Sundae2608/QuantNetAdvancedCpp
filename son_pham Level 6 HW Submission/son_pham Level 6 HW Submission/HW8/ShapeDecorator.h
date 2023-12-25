/*
* Advanced C++ and Modern Design
* Level 6 - Homework 8
* Author: Son Pham
* Shape Decorator header
*/

#ifndef SHAPEDECORATOR_H
#define SHAPEDECORATOR_H

#include "Shape.h"

class ShapeDecorator : public Shape {
public:
  ShapeDecorator();
  ShapeDecorator(Shape *shape);
  virtual ~ShapeDecorator() {}

  Shape *GetShape() const;
  void SetShape(Shape *shape);

  virtual void print(std::ostream &os) const override = 0;
  virtual Shape *Clone() const override;

private:
  Shape *decoratedShape;
};

#endif // SHAPEDECORATOR_H