#include "pch.h"
#include "Circle.h"

Circle::Circle(double radius)
{ 
	this->radius = radius;
}

Circle::~Circle()
{
}

Point3D Circle::derivativeOfPoint(double step) const
{
	return Point3D {radius * -sin(step), radius * cos(step), 0};
}

Point3D Circle::getPointOnCurve(double step) const
{
	return Point3D {radius * cos(step), radius * sin(step), 0};
}

const double& Circle::getRadius() const
{
	return radius;
}
