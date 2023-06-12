#pragma once

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Ñurve.h"

class CURVESLIBRARY_API Circle : public ICurve
{
public:
	Circle(double radius);
	virtual ~Circle() override;

	Point3D derivativeOfPoint(double step) const override;

	Point3D getPointOnCurve(double step) const override;

	const double& getRadius() const;

private:
	double radius {};
};

#endif

