#pragma once

#ifndef HELIX_H
#define HELIX_H

#include "Ñurve.h"

class CURVESLIBRARY_API Helix : public ICurve
{
public:
	Helix(double radius, double slope);
	virtual ~Helix() override;

	Point3D derivativeOfPoint(double step) const override;

	Point3D getPointOnCurve(double step) const override;

private:
	double radius {}, slope {};
};

#endif

