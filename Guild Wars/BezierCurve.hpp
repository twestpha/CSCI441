#ifndef bezier_curve_h
#define bezier_curve_h

#include <stdio.h>
#include <vector>

#include "Point.hpp"
#include "gl_includes.hpp"

class BezierCurve {
public:
	BezierCurve();
	BezierCurve(std::vector<Point> control_points);

	void toggleControlCageVisibility();
	void toggleCurveVisibility();

	bool isCurveVisible(){ return curveIsVisible; }
	bool isControlCageVisible(){ return controlCageIsVisible; }

	Point getControlPoint(int index);

	float getMaximumT();
	int getNumberOfControlPoints();

	Point getPointFromT(float t);
private:
	bool controlCageIsVisible;
	bool curveIsVisible;

	void calculateMaximumT();

	Point interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t);
	std::vector<Point> control_points;
	float t_max;
};

#endif
