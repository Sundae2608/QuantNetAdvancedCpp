/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Print Visitor header
*/

#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

#include "ShapeVisitor.h"

class PrintVisitor : public ShapeVisitor {
public:
  virtual void Visit(Point &p) override;
  virtual void Visit(Line &l) override;
  virtual void Visit(Circle &c) override;
  virtual void Visit(ShapeComposite &sc) override;
};

#endif // PRINTVISITOR_H