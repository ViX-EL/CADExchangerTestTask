#include "pch.h"
#include "Helix.h"

Helix::Helix(double radius, double slope)
{
	this->radius = radius;
	this->slope = slope;
}

Helix::~Helix()
{
}

Point3D Helix::derivativeOfPoint(double step) const
{
	return Point3D {-sin(step), slope * step, radius * cos(step)};
}

Point3D Helix::getPointOnCurve(double step) const
{
	return Point3D {radius * cos(step), slope * step, radius * sin(step)};
}
