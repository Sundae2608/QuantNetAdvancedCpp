/*
* Advanced C++ and Modern Design
* Level 6 - Homework 8
* Author: Son Pham
* Shape
*/

#include "Shape.h"

std::ostream &operator<<(std::ostream &os, const Shape &shp) {
  shp.print(os);
  return os;
}