/*
* Advanced C++ and Modern Design
* Level 6 - Homework 6
* Author: Son Pham
* Exact Distance header
*/

#ifndef EXACTDISTANCE_H
#define EXACTDISTANCE_H

#include "DistanceStrategy.h"

class ExactDistance : public DistanceStrategy {
public:
    virtual double CalculateDistance(const Point& p1,
        const Point& p2) const override;
};

#endif // EXACTDISTANCE_H