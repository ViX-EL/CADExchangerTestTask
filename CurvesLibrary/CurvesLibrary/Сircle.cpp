#include "pch.h"
#include "Ñircle.h"

Ñircle::Ñircle(double radius)
{ 
	this->radius = radius;
}

Ñircle::~Ñircle()
{
}

Point3D Ñircle::derivativeOfPoint(double step) const
{
	return Point3D {radius * -sin(step), radius * cos(step), 0};
}

Point3D Ñircle::getPointOnCurve(double step) const
{
	return Point3D {radius * cos(step), radius * sin(step), 0};
}

const double& Ñircle::getRadius() const
{
	return radius;
}
