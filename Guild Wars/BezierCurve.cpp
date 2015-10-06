#include "BezierCurve.hpp"
#include "Point.hpp"

BezierCurve::BezierCurve(){
	controlCageIsVisible = true;
	curveIsVisible = true;
}

BezierCurve::BezierCurve(std::vector<Point> control_points){
	controlCageIsVisible = true;
	curveIsVisible = true;
	this->control_points = control_points;

	calculateMaximumT();
}

void BezierCurve::toggleControlCageVisibility(){
	controlCageIsVisible=!controlCageIsVisible;
}

void BezierCurve::toggleCurveVisibility(){
	curveIsVisible=!curveIsVisible;
}

Point BezierCurve::getPointFromT(float t){
	// Which chunk are we on?
	int number_chunks = ((control_points.size() - 4) / 3) + 1;
	int which_chunk = int(float(number_chunks)*t);
	float t_per_chunk = 1.0/float(number_chunks);
	float normalized_t = t - (t_per_chunk * which_chunk);
	normalized_t/=t_per_chunk;

	Point a = control_points[(which_chunk*3)+0];
	Point b = control_points[(which_chunk*3)+1];
	Point c = control_points[(which_chunk*3)+2];
	Point d = control_points[(which_chunk*3)+3];

	return interpolatePointFromCurveAlongT(a, b, c, d, normalized_t);
}

Point BezierCurve::interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t){
	return ((-1*a + 3*b - 3*c + d)*(t*t*t)) +
					((3*a - 6*b + 3*c)*(t*t)) +
					((-3*a + 3*b)*(t)) +
					(a);
}

Point BezierCurve::getControlPoint(int index) {
	// return (control_points[index] + getPosition());
	return control_points[index];
}

float BezierCurve::getMaximumT() {
	return t_max;
}

void BezierCurve::calculateMaximumT() {
	t_max = ((getNumberOfControlPoints() - 4) / 3) + 1;
}

int BezierCurve::getNumberOfControlPoints() {
	return control_points.size();
}
