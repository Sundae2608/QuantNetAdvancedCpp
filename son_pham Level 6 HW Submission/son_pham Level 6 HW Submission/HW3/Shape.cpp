/*
* Advanced C++ and Modern Design
* Level 6 - Homework 3
* Author: Son Pham
* Shape class header
*/

#include "Shape.h"

std::ostream& operator<<(std::ostream& os, const Shape& shp) {
	shp.print(os);
	return os;
}