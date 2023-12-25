/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Translate Visitor
*/
#include "TranslateVisitor.h"
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "ShapeComposite.h"

TranslateVisitor::TranslateVisitor(double x, double y)
    : xTranslation(x), yTranslation(y) {}

void TranslateVisitor::Visit(Point &p) {
  p.x(p.x() + xTranslation);
  p.y(p.y() + yTranslation);
}

void TranslateVisitor::Visit(Line &l) {
  Visit(*l.MutableP1());
  Visit(*l.MutableP2());
}

void TranslateVisitor::Visit(Circle &c) { Visit(*c.MutableCenterPoint()); }

void TranslateVisitor::Visit(ShapeComposite &sc) { sc.Accept(*this); }