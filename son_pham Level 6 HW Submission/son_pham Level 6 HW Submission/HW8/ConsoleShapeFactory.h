/*
* Advanced C++ and Modern Design
* Level 6 - Homework 8
* Author: Son Pham
* Console Shape Factory header
*/

#ifndef CONSOLESHAPEFACTORY_H
#define CONSOLESHAPEFACTORY_H

#include "ShapeFactory.h"

class ConsoleShapeFactory : public ShapeFactory {
public:
  virtual Shape *CreateCircle() override;
  virtual Shape *CreateLine() override;
  virtual Shape *CreatePoint() override;
};

#endif // CONSOLESHAPEFACTORY_H