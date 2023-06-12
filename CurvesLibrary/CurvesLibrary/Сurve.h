#pragma once

#ifndef CURVE_H
#define CURVE_H

#include <math.h>

#ifdef CURVESLIBRARY_EXPORTS
#define CURVESLIBRARY_API __declspec(dllexport)
#else
#define CURVESLIBRARY_API __declspec(dllimport)
#endif

struct CURVESLIBRARY_API Point3D
{
	double x {}, y {}, z {};  // width, high, depth
};

class CURVESLIBRARY_API ICurve
{
public:
	virtual ~ICurve() {}; //виртуальный деструктор для полиморфного использования производных объектов

	virtual Point3D getPointOnCurve(double step) const = 0; //step - parametr t

	virtual Point3D derivativeOfPoint(double step) const = 0;
};

#endif