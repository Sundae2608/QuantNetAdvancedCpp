/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Shape Composite header
*/

#ifndef SHAPE_COMPOSITE_H
#define SHAPE_COMPOSITE_H

#include "Shape.h"
#include "ShapeVisitor.h"

#include <list>

class ShapeComposite : public Shape {
public:
  ShapeComposite();
  ~ShapeComposite();

  void AddShape(Shape *s);
  typedef std::list<Shape *>::iterator iterator;
  typedef std::list<Shape *>::const_iterator const_iterator;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  size_t Count() const;
  void Accept(ShapeVisitor &visitor);

  void print(std::ostream &os) const;
  virtual ShapeComposite *Clone() const override;

private:
  std::list<Shape *> shapes_;
};

#endif // SHAPE_COMPOSITE_H