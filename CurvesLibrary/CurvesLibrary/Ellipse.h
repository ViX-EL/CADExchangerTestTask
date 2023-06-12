#pragma once

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Ñurve.h"

class CURVESLIBRARY_API Ellipse : public ICurve
{
public:
	Ellipse(double majorSemiaxis, double semiminorAxis);
	virtual ~Ellipse() override;

	Point3D derivativeOfPoint(double step) const override;

	Point3D getPointOnCurve(double step) const override;

private:
	double majorSemiaxis {}, semiminorAxis {};
};

#endif

