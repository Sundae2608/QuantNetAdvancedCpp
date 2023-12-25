/*
* Advanced C++ and Modern Design
* Level 6 - Homework 4
* Author: Son Pham
* Circle class header file
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "Shape.h"

class Circle : public Shape {
public:
	Circle();
	Circle(const Point& c, double r);
	Circle(const Circle& c);
	Circle& operator=(const Circle& c);
	virtual ~Circle() override;

	Point CenterPoint() const;
	double Radius() const;
	void CenterPoint(const Point& centre);
	void Radius(double radius);
	virtual void print(std::ostream& os) const override;
	virtual Circle* Clone() const override;

private:
	Point center_;
	double radius_;
};

#endif // CIRCLE_H