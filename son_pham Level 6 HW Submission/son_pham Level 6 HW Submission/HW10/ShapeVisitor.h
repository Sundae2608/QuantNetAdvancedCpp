/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Shape Visitor header
*/

#ifndef SHAPEVISITOR_H
#define SHAPEVISITOR_H

class Point;
class Line;
class Circle;
class ShapeComposite;

class ShapeVisitor {
public:
  virtual ~ShapeVisitor() {}
  virtual void Visit(Point &p) = 0;
  virtual void Visit(Line &l) = 0;
  virtual void Visit(Circle &c) = 0;
  virtual void Visit(ShapeComposite &sc) = 0;
};

#endif // SHAPEVISITOR_H