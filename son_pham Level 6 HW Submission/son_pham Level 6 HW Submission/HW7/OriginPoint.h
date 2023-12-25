/*
* Advanced C++ and Modern Design
* Level 6 - Homework 7
* Author: Son Pham
* OriginPoint header
*/

#ifndef ORIGINPOINT_H
#define ORIGINPOINT_H

// This is thanks to the instruction in this forum
// post
// https://quantnet.com/threads/1-why-does-singleton-pattern-include-singleton-cpp-instead-of-singleton-hpp.25002/
// It is very intriguing to learn that I need to include
// the CPP file here.
#include "Singleton.cpp"

class Point;

class OriginPoint : public Singleton<Point> {
public:
	OriginPoint() = default;
	OriginPoint(const OriginPoint& source) = delete; // copy constructor
	~OriginPoint() = default;

	// Assignment operator
	OriginPoint& operator=(const OriginPoint& source) = delete;
};

#endif // ORIGINPOINT_H