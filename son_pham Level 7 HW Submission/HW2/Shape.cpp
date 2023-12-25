#include "Shape.h"

std::ostream &operator<<(std::ostream &os, const Shape &shp) {
  shp.print(os);
  return os;
}