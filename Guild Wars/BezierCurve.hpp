#ifndef bezier_curve_h
#define bezier_curve_h

#include <stdio.h>
#include <vector>

#include "Point.hpp"
#include "gl_includes.hpp"

class BezierCurve {
public:
	BezierCurve();

	void addPoint(Point p);
	void draw(int resolution);

	void toggleControlCageVisibility();
	void toggleCurveVisibility();

	bool isCurveVisible(){ return curveIsVisible; }
	bool isControlCageVisible(){ return controlCageIsVisible; }

	Point getPointFromT(float t);
private:
	bool controlCageIsVisible;
	bool curveIsVisible;

	void drawPoints();
	void drawControlCage();
	void drawCurve(int resolution);
	Point interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t);
	std::vector<Point> points;
};

#endif
