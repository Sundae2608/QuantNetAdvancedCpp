/*
* Advanced C++ and Modern Design
* Level 6 - Homework 6
* Author: Son Pham
* Distance strategy
*/

#ifndef DISTANCESTRATEGY_H
#define DISTANCESTRATEGY_H

class Point;

class DistanceStrategy {
public:
	virtual double CalculateDistance(const Point& p1, const Point& p2) const = 0;
};

#endif // DISTANCESTRATEGY_H