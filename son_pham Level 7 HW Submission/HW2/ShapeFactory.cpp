#include "ShapeFactory.h"

ShapeFactory::ShapeFactory(
    std::function<Shape *(std::initializer_list<double>)> createMethod)
    : createShape(createMethod) {}

Shape *ShapeFactory::CreateShape(std::initializer_list<double> args) {
  return createShape(args);
}