#include "pch.h"
#include "Ellipse.h"

Ellipse::Ellipse(double majorSemiaxis, double semiminorAxis)
{
	this->majorSemiaxis = majorSemiaxis;
	this->semiminorAxis = semiminorAxis;
}

Ellipse::~Ellipse()
{
}

Point3D Ellipse::derivativeOfPoint(double step) const
{
	return Point3D {majorSemiaxis * -sin(step), semiminorAxis * cos(step), 0};
}

Point3D Ellipse::getPointOnCurve(double step) const
{
	return Point3D {majorSemiaxis * cos(step), semiminorAxis * sin(step), 0};
}
