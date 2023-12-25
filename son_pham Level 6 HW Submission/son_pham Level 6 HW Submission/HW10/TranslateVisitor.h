/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Translate Visitor header
*/

#ifndef TRANSLATEVISITOR_H
#define TRANSLATEVISITOR_H

#include "ShapeVisitor.h"

class TranslateVisitor : public ShapeVisitor {
private:
  double xTranslation;
  double yTranslation;

public:
  TranslateVisitor(double x, double y);
  virtual void Visit(Point &p) override;
  virtual void Visit(Line &l) override;
  virtual void Visit(Circle &c) override;
  virtual void Visit(ShapeComposite &sc) override;
};

#endif // TRANSLATEVISITOR_H