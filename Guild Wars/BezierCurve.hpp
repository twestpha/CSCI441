#ifndef bezier_curve_h
#define bezier_curve_h

#include <stdio.h>
#include <vector>

#include "Point.hpp"
#include "Vector3.hpp"
#include "gl_includes.hpp"

using namespace std;

class BezierCurve {
public:
	BezierCurve();
	BezierCurve(std::vector<Point> control_points);

	Point getControlPoint(int index);

	float getMaximumT();
	int getNumberOfControlPoints();

	Point getPointFromT(float t);
	Point getPointFromS(float s);

	Vector3 getTangentFromT(float t);

	Point getParameterizedPointAtIndex(int index);
	int getNumberOfParameterizedPoints();

private:
	void calculateMaximumT();

	void calculateParameterizedPoints();

	Point interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t);
	Point interpolatePointFromCurveAlongTDerivative(Point a, Point b, Point c, Point d, float t);

	void addParameterizedPoint(Point& point);


	float calculateLength();

	vector<Point> control_points;
	vector<Point> parameterized_points;

	float t_max;
};

#endif
