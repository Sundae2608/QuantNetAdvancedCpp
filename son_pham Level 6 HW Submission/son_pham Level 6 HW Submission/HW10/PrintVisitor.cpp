/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Point Visitor
*/

#include "PrintVisitor.h"
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "ShapeComposite.h"
#include "ShapeDecorator.h"
#include <iostream>

void PrintVisitor::Visit(Point &p) {
  std::cout << "Point: (" << p.x() << ", " << p.y() << ")" << std::endl;
}

void PrintVisitor::Visit(Line &l) {
  std::cout << "Line: " << l.p1() << " to " << l.p2() << std::endl;
}

void PrintVisitor::Visit(Circle &c) {
  std::cout << "Circle: Center " << c.CenterPoint();
  std::cout << ", Radius " << c.Radius() << std::endl;
}

void PrintVisitor::Visit(ShapeComposite &sc) {
  std::cout << "Shape Composite:" << std::endl;
  sc.Accept(*this);
}