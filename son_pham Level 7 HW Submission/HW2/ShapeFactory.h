#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.h" // Assuming you have a Shape base class
#include <functional>

class ShapeFactory {
public:
  ShapeFactory(
      std::function<Shape *(std::initializer_list<double>)> createMethod);

  Shape *CreateShape(std::initializer_list<double> args);

private:
  std::function<Shape *(std::initializer_list<double>)> createShape;
};

#endif // SHAPEFACTORY_H