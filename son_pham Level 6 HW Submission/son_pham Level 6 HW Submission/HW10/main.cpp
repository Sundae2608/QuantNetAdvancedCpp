/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Main implementation
*/

#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "PrintVisitor.h"
#include "ShapeComposite.h"
#include "TranslateVisitor.h"
#include <iostream>

int main() {
  Point p(1.0, 2.0);
  Line l(Point(0.0, 0.0), Point(3.0, 4.0));
  Circle c(Point(5.0, 5.0), 2.0);

  ShapeComposite composite;
  composite.AddShape(&p);
  composite.AddShape(&l);
  composite.AddShape(&c);

  PrintVisitor printVisitor;
  printVisitor.Visit(composite);

  TranslateVisitor translateVisitor(10.0, -10.0);
  translateVisitor.Visit(composite);

  std::cout << std::endl;
  std::cout << "After translation of x + 10.0 and y - 10.0:" << std::endl;
  printVisitor.Visit(composite);

  return 0;
}