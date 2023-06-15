#include "RandomCurvesData.h"

std::mt19937 initializingRandomNumberGenerator()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	return generator;
}

double randomInIntervalDouble(const MinMaxPositiveDouble& interval, std::mt19937& generator)
{
	std::uniform_real_distribution<> distribution(interval.getMin(), interval.getMax());

	return distribution(generator);

	//return static_cast<double>(rand()) / RAND_MAX * (interval.getMax() - interval.getMin()) + interval.getMin();
}

int randomInIntervalPositiveInt(const MinMaxPositiveInt& interval, std::mt19937& generator)
{
	std::uniform_int_distribution<> distribution(interval.getMin(), interval.getMax());

	return distribution(generator);

	//return interval.getMin() + rand() % (interval.getMax() - interval.getMin() + 1);
}

MinMaxPositiveDouble::MinMaxPositiveDouble(double min, double max)
{
	setMinMax(min, max);
}

void MinMaxPositiveDouble::setMinMax(double min, double max)
{
	assert(min < max && min >= 0 && max > 0 && "max и min не должны быть отрицательными, а так же max должен быть больше min!");

	this->min = min;
	this->max = max;
}

double MinMaxPositiveDouble::getMin() const
{
	return min;
}

double MinMaxPositiveDouble::getMax() const
{
	return max;
}

MinMaxPositiveInt::MinMaxPositiveInt(int min, int max)
{
	setMinMax(min, max);
}

void MinMaxPositiveInt::setMinMax(int min, int max)
{
	assert(min < max && min >= 0 && max > 0 && "max и min не должны быть отрицательными, а так же max должен быть больше min!");

	this->min = min;
	this->max = max;
}

int MinMaxPositiveInt::getMin() const
{
	return min;
}

int MinMaxPositiveInt::getMax() const
{
	return max;
}

RandomCurvesData::RandomCurvesData(const MinMaxPositiveInt& circlesCount, const MinMaxPositiveInt& ellipsesCount, const MinMaxPositiveInt& helixesCount,
								   const MinMaxPositiveDouble& circleRadius, const MinMaxPositiveDouble& ellipseMajorSemiaxis,
								   const MinMaxPositiveDouble& ellipseSemiminorAxis, const MinMaxPositiveDouble& helixRadius,
								   const MinMaxPositiveDouble& helixSlope)
{
	randomNumberGenerator = initializingRandomNumberGenerator();

	//srand(static_cast<unsigned int>(time(0)));

	int resultCirclesCount {randomInIntervalPositiveInt(circlesCount, randomNumberGenerator)};
	int resultEllipsesCount {randomInIntervalPositiveInt(ellipsesCount, randomNumberGenerator)};
	int resultHelixesCount {randomInIntervalPositiveInt(helixesCount, randomNumberGenerator)};

	long totalCurvesCount = resultCirclesCount + resultEllipsesCount + resultHelixesCount;

	curves.reserve(totalCurvesCount);
	circlesPtrs.reserve(resultCirclesCount);

	enum CurvesTypes: int
	{
		circle, ellipse, helix
	};

	while (totalCurvesCount > 0)
	{
		CurvesTypes currCurveType = static_cast<CurvesTypes>(randomInIntervalPositiveInt(MinMaxPositiveInt(0, 2), randomNumberGenerator));

		switch (currCurveType)
		{
		case circle:
			if (resultCirclesCount > 0)
			{
				addCircle(circleRadius);
				resultCirclesCount--;
				totalCurvesCount--;
			}
			break;
		case ellipse:
			if (resultEllipsesCount > 0)
			{
				addEllipse(ellipseMajorSemiaxis, ellipseSemiminorAxis);
				resultEllipsesCount--;
				totalCurvesCount--;
			}
			break;
		case helix:
			if (resultHelixesCount > 0)
			{
				addHelix(helixRadius, helixSlope);
				resultHelixesCount--;
				totalCurvesCount--;
			}
			break;
		}
	}

	circlePtrsSort();
}

void RandomCurvesData::printPointOnCurve(int curveIndex, double step) const
{
	Point3D point(curves[curveIndex]->getPointOnCurve(step));
	std::cout << "X: " << point.x << " Y: " << point.y << " Z: " << point.z << std::endl;
}

void RandomCurvesData::printDerivativeOfPoint(int curveIndex, double step) const
{
	Point3D point(curves[curveIndex]->derivativeOfPoint(step));
	std::cout << "X: " << point.x << " Y: " << point.y << " Z: " << point.z << std::endl;
}

void RandomCurvesData::printPointsOfAllCurves(double step) const
{
	std::cout << "Points on each curve at t = :" << step << std::endl;
	for (size_t currCurve = 0; currCurve < curves.size(); currCurve++)
		printPointOnCurve(currCurve, step);
}

void RandomCurvesData::printPointDerivativesOfAllCurves(double step) const
{
	std::cout << "Derivatives on each curve at t = :" << step << std::endl;
	for (size_t currCurve = 0; currCurve < curves.size(); currCurve++)
		printDerivativeOfPoint(currCurve, step);
}

void RandomCurvesData::addCircle(const MinMaxPositiveDouble& radius)
{
	double resultRadius = randomInIntervalDouble(radius, randomNumberGenerator);
	circlesPtrs.push_back(std::make_shared<Circle>(resultRadius));
	curves.push_back(circlesPtrs.back());
}

void RandomCurvesData::addEllipse(const MinMaxPositiveDouble& majorSemiaxis, const MinMaxPositiveDouble& semiminorAxis)
{
	double resultMajorSemiaxis = randomInIntervalDouble(majorSemiaxis, randomNumberGenerator);
	double resultSemiminorAxis = randomInIntervalDouble(semiminorAxis, randomNumberGenerator);
	curves.push_back(std::make_shared<Ellipse>(resultMajorSemiaxis, resultSemiminorAxis));
}

void RandomCurvesData::addHelix(const MinMaxPositiveDouble& radius, const MinMaxPositiveDouble& slope)
{
	double resultRadius = randomInIntervalDouble(radius, randomNumberGenerator);
	double resultSlope = randomInIntervalDouble(slope, randomNumberGenerator);
	curves.push_back(std::make_shared<Helix>(resultRadius, resultSlope));
}

void RandomCurvesData::circlePtrsSort()
{
	std::sort(circlesPtrs.begin(), circlesPtrs.end(), 
		[](const std::shared_ptr<Circle>& right, const std::shared_ptr<Circle>& left)
		{ return right->getRadius() < left->getRadius(); });
}

double RandomCurvesData::calculateSumOfCircleRadii() const
{
	double sum = 0.0f;
	#pragma omp parallel reduction (+: sum)
	{
		#pragma omp for
		for (size_t currCirclePtr = 0; currCirclePtr < circlesPtrs.size(); currCirclePtr++)
		{
			sum =+ circlesPtrs[currCirclePtr]->getRadius();
		}
	}
	return sum;
}
