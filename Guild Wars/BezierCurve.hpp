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

	Point getPointFromT(float t);
private:
	float calculateMaximumT();
	float calculateLength();

	Point interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t);

	std::vector<Point> control_points;
};

#endif
