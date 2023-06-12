#include "pch.h"
#include "�ircle.h"

�ircle::�ircle(double radius)
{ 
	this->radius = radius;
}

�ircle::~�ircle()
{
}

Point3D �ircle::derivativeOfPoint(double step) const
{
	return Point3D {radius * -sin(step), radius * cos(step), 0};
}

Point3D �ircle::getPointOnCurve(double step) const
{
	return Point3D {radius * cos(step), radius * sin(step), 0};
}

const double& �ircle::getRadius() const
{
	return radius;
}
