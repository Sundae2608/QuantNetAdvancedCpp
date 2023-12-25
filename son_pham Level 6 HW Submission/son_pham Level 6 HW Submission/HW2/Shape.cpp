/*
* Advanced C++ and Modern Design
* Level 6 - Homework 2
* Author: Son Pham
* Shape class
*/

#include "Shape.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const Shape& shp) {
	shp.print(os);
	return os;
}