#ifndef bezier_curve_h
#define bezier_curve_h

#include <stdio.h>
#include <vector>
#include <unordered_map>

#include "gl_includes.hpp"

#include "Point.hpp"
#include "Vector3.hpp"

class BezierCurve {
public:
	BezierCurve();
	BezierCurve(std::vector<Point> control_points);

	Point getControlPoint(int index);

	float getMaximumT();
	int getNumberOfControlPoints();
	float calculateLength();

	Point getPointFromT(float t);
	Point getPointFromS(float s);
private:
	float calculateMaximumT();

	Point interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t);

	std::vector<Point> control_points;
};

#endif
