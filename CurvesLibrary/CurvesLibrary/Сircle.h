#pragma once

#ifndef CIRCLE_H
#define CIRCLE_H

#include "�urve.h"

class CURVESLIBRARY_API �ircle : public ICurve
{
public:
	�ircle(double radius);
	virtual ~�ircle() override;

	Point3D derivativeOfPoint(double step) const override;

	Point3D getPointOnCurve(double step) const override;

	const double& getRadius() const;

private:
	double radius {};
};

#endif

