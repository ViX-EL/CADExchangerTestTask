#pragma once

#include <ctime>
#include <memory>
#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>
#include <omp.h>
#include <random>

#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"

struct MinMaxPositiveDouble
{
public:
	MinMaxPositiveDouble(double min, double max);

	void setMinMax(double min, double max);
	double getMin() const;
	double getMax() const;
private:
	double min {};
	double max {};
};

struct MinMaxPositiveInt
{
	MinMaxPositiveInt(int min, int max);

	void setMinMax(int min, int max);
	int getMin() const;
	int getMax() const;
private:
	int min {};
	int max {};
};

std::mt19937 initializingRandomNumberGenerator();
double randomInIntervalDouble(const MinMaxPositiveDouble& interval, std::mt19937& generator);
int randomInIntervalPositiveInt(const MinMaxPositiveInt& interval, std::mt19937& generator);

class RandomCurvesData
{
public:
	RandomCurvesData(const MinMaxPositiveInt& circlesCount, const MinMaxPositiveInt& ellipsesCount, const MinMaxPositiveInt& helixesCount,
					 const MinMaxPositiveDouble& circleRadius = MinMaxPositiveDouble(1.0, 10.0), 
					 const MinMaxPositiveDouble& ellipseMajorSemiaxis = MinMaxPositiveDouble(1.0, 5.0),
					 const MinMaxPositiveDouble& ellipseSemiminorAxis = MinMaxPositiveDouble(1.0, 5.0),
					 const MinMaxPositiveDouble& helixRadius = MinMaxPositiveDouble(1.0, 10.0),
					 const MinMaxPositiveDouble& helixSlope = MinMaxPositiveDouble(1.0, 10.0));

	void printPointsOfAllCurves(double step) const;
	void printPointDerivativesOfAllCurves(double step) const;

	double calculateSumOfCircleRadii() const;

private:
	std::vector< std::shared_ptr<ICurve>> curves;
	std::vector<std::shared_ptr<Circle>> circlesPtrs;

	void printPointOnCurve(int curveIndex, double step) const;
	void printDerivativeOfPoint(int curveIndex, double step) const;

	void addCircle(const MinMaxPositiveDouble& radius);
	void addEllipse(const MinMaxPositiveDouble& majorSemiaxis, const MinMaxPositiveDouble& semiminorAxis);
	void addHelix(const MinMaxPositiveDouble& radius, const MinMaxPositiveDouble& slope);

	void circlePtrsSort();

	std::mt19937 randomNumberGenerator;
};

