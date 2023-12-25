/*
* Advanced C++ and Modern Design
* Level 6 - Homework 7
* Author: Son Pham
* main file testing the implementation of factory methods
*/

#include "ConsoleShapeFactory.h"
#include "ShapeFactory.h"
#include <iostream>

int main() {
	ConsoleShapeFactory consoleFactory;

	Shape* circle = consoleFactory.CreateCircle();
	Shape* line = consoleFactory.CreateLine();
	Shape* point = consoleFactory.CreatePoint();

	std::cout << *circle << std::endl;
	std::cout << *line << std::endl;
	std::cout << *point << std::endl;
	return 0;
}