#pragma once

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Ñurve.h"

class CURVESLIBRARY_API Ñircle : public ICurve
{
public:
	Ñircle(double radius);
	virtual ~Ñircle() override;

	Point3D derivativeOfPoint(double step) const override;

	Point3D getPointOnCurve(double step) const override;

	const double& getRadius() const;

private:
	double radius {};
};

#endif

