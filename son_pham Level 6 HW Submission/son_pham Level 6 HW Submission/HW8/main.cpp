#include "Circle.h"
#include "Line.h"
#include "NameDecorator.h"
#include "Point.h"
#include "Shape.h"
#include "ShapeDecorator.h"
#include <iostream>

int main() {
  Point center(0.0, 0.0);
  double radius = 5.0;
  Shape *circle = new Circle(center, radius);

  // Decorate the circle with a name
  Shape *namedCircle = new NameDecorator(circle, "My Circle");

  // Draw and print the decorated circle with its name
  std::cout << "Drawing decorated circle: ";
  std::cout << *namedCircle;
  std::cout << std::endl;

  // Clone the decorated circle and print it
  Shape *clonedNamedCircle = namedCircle->Clone();
  std::cout << "Drawing cloned decorated circle: ";
  std::cout << *clonedNamedCircle;
  std::cout << std::endl;
  return 0;
}