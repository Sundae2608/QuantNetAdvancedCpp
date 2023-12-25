/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Circle header
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "Shape.h"
#include "ShapeVisitor.h"

class Circle : public Shape {
public:
  Circle();
  Circle(const Point &c, double r);
  Circle(const Circle &c);
  Circle &operator=(const Circle &c);
  virtual ~Circle() override;

  Point CenterPoint() const;
  double Radius() const;
  void CenterPoint(const Point &centre);
  Point *MutableCenterPoint();
  void Radius(double radius);
  virtual void print(std::ostream &os) const override;
  virtual Circle *Clone() const override;
  void Accept(ShapeVisitor &visitor);

private:
  Point center_;
  double radius_;
};

#endif // CIRCLE_H