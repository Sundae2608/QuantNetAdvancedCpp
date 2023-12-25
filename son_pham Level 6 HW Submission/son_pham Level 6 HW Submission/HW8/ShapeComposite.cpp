/*
* Advanced C++ and Modern Design
* Level 6 - Homework 8
* Author: Son Pham
* Shape Composite
*/

#include "ShapeComposite.h"

#include <iostream>

ShapeComposite::ShapeComposite() {}
ShapeComposite::~ShapeComposite() {}

void ShapeComposite::AddShape(Shape *s) { shapes_.push_back(s); }

ShapeComposite::iterator ShapeComposite::begin() { return shapes_.begin(); }

ShapeComposite::iterator ShapeComposite::end() { return shapes_.end(); }

ShapeComposite::const_iterator ShapeComposite::begin() const {
  return shapes_.begin();
}

ShapeComposite::const_iterator ShapeComposite::end() const {
  return shapes_.end();
}

size_t ShapeComposite::Count() const { return shapes_.size(); }

void ShapeComposite::print(std::ostream &os) const {
  for (const Shape *shape : shapes_) {
    os << *shape << std::endl;
    const ShapeComposite *composite =
        dynamic_cast<const ShapeComposite *>(shape);
    if (composite) {
      os << *composite;
    }
  }
}

ShapeComposite *ShapeComposite::Clone() const {
  return new ShapeComposite(*this);
}