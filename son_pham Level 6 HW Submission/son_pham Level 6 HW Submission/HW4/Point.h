/*
* Advanced C++ and Modern Design
* Level 6 - Homework 4
* Author: Son Pham
* Point class header file
*/

#ifndef POINT_H
#define POINT_H

#include "Shape.h"

#include <iostream>

class Point : public Shape {
public:
	Point();
	Point(double xs, double ys);
	Point(const Point& pt);
	Point& operator=(const Point& pt);
	double Distance(const Point& p) const;
	double Distance() const; // Distance to origin
	virtual void print(std::ostream& os) const override;
	virtual Point* Clone() const override;

	double x() const;
	double y() const;
	void x(double xs);
	void y(double ys);

private:
	double x_;
	double y_;
};

#endif // POINT_H