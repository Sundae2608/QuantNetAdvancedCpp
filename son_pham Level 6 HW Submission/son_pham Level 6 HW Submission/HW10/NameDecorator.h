/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Name Decorator header
*/

#ifndef NAMEDECORATOR_H
#define NAMEDECORATOR_H

#include "ShapeDecorator.h"
#include <string>

class NameDecorator : public ShapeDecorator {
public:
  NameDecorator();
  NameDecorator(Shape *shape, const std::string &name);

  std::string GetName() const;
  void SetName(const std::string &name);

  virtual void print(std::ostream &os) const;
  virtual Shape *Clone() const override;

private:
  std::string name;
};

#endif // NAMEDECORATOR_H