#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "Shape.h"

class ShapeFactory {
public:
  virtual ~ShapeFactory() {}
  virtual Shape *CreateCircle() = 0;
  virtual Shape *CreateLine() = 0;
  virtual Shape *CreatePoint() = 0;
  virtual std::tuple<Point *, Line *, Circle *> CreateShapes() = 0;
};

#endif // SHAPEFACTORY_H