#ifndef CONSOLESHAPEFACTORY_H
#define CONSOLESHAPEFACTORY_H

#include "ShapeFactory.h"

class ConsoleShapeFactory : public ShapeFactory {
public:
  virtual Shape *CreateCircle() override;
  virtual Shape *CreateLine() override;
  virtual Shape *CreatePoint() override;
  virtual std::tuple<Point *, Line *, Circle *> CreateShapes() override;
};

#endif // CONSOLESHAPEFACTORY_H