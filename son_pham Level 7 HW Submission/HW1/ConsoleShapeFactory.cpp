#include "ConsoleShapeFactory.h"
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include <iostream>
#include <tuple>

Shape *ConsoleShapeFactory::CreateCircle() {
  double centerX, centerY, radius;
  std::cout << "Enter the center coordinates of the circle (x y): ";
  std::cin >> centerX >> centerY;
  std::cout << "Enter the radius of the circle: ";
  std::cin >> radius;
  return new Circle(Point(centerX, centerY), radius);
}

Shape *ConsoleShapeFactory::CreateLine() {
  double x1, y1, x2, y2;
  std::cout << "Enter the coordinates of the start point (x y): ";
  std::cin >> x1 >> y1;
  std::cout << "Enter the coordinates of the end point (x y): ";
  std::cin >> x2 >> y2;
  return new Line(Point(x1, y1), Point(x2, y2));
}

Shape *ConsoleShapeFactory::CreatePoint() {
  double x, y;
  std::cout << "Enter the coordinates of the point (x y): ";
  std::cin >> x >> y;
  return new Point(x, y);
}

std::tuple<Point *, Line *, Circle *> ConsoleShapeFactory::CreateShapes() {
  double centerX, centerY, radius;
  double x1, y1, x2, y2;
  double x, y;

  std::cout << "Enter the center coordinates of the circle (x y): ";
  std::cin >> centerX >> centerY;
  std::cout << "Enter the radius of the circle: ";
  std::cin >> radius;
  Point *point = new Point(centerX, centerY);
  Circle *circle = new Circle(*point, radius);

  std::cout << "Enter the coordinates of the start point (x y): ";
  std::cin >> x1 >> y1;
  std::cout << "Enter the coordinates of the end point (x y): ";
  std::cin >> x2 >> y2;
  Line *line = new Line(Point(x1, y1), Point(x2, y2));

  std::cout << "Enter the coordinates of the point (x y): ";
  std::cin >> x >> y;
  Point *singlePoint = new Point(x, y);

  return std::make_tuple(point, line, circle);
}
