/*
* Advanced C++ and Modern Design
* Level 6 - Homework 6
* Author: Son Pham
* Point header file
*/

#ifndef POINT_H
#define POINT_H

#include "DistanceStrategy.h"
#include "Shape.h"

#include <iostream>

class Point : public Shape {
public:
	Point();
	Point(double xs, double ys);
	Point(const Point& pt);
	Point& operator=(const Point& pt);
	static void SetDistanceStrategy(DistanceStrategy* strategy);
	double Distance(const Point& p) const;
	double Distance() const; // Distance to origin
	double Distance(const Point& p, const DistanceStrategy& strategy) const;
	virtual void print(std::ostream& os) const override;
	virtual Point* Clone() const override;

	double x() const;
	double y() const;
	void x(double xs);
	void y(double ys);

private:
	double x_;
	double y_;
	static DistanceStrategy* distanceStrategy_;
};

#endif // POINT_H