#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.h"

class ShapeFactory {
public:
  virtual ~ShapeFactory() {}
  virtual Shape *CreateCircle() = 0;
  virtual Shape *CreateLine() = 0;
  virtual Shape *CreatePoint() = 0;
};

#endif // SHAPEFACTORY_H