#include "BezierCurve.hpp"

BezierCurve::BezierCurve(){

}

BezierCurve::BezierCurve(std::vector<Point> control_points){
	this->control_points = control_points;

	calculateMaximumT();
	calculateParameterizedPoints();
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

Point BezierCurve::getPointFromS(float s){
	int index = s * getNumberOfParameterizedPoints();
	return getParameterizedPointAtIndex(index);
}

Point BezierCurve::getParameterizedPointAtIndex(int index) {
	return parameterized_points[index];
}

int BezierCurve::getNumberOfParameterizedPoints() {
	return parameterized_points.size();
}

Vector3 BezierCurve::getTangentFromT(float t){
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

	Point v = interpolatePointFromCurveAlongTDerivative(a, b, c, d, normalized_t);
	return Vector3(v.getX(), v.getY(), v.getZ());
}

Point BezierCurve::interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t){
	return ((-1*a + 3*b - 3*c + d)*(t*t*t)) +
					((3*a - 6*b + 3*c)*(t*t)) +
					((-3*a + 3*b)*(t)) +
					(a);
}

Point BezierCurve::interpolatePointFromCurveAlongTDerivative(Point a, Point b, Point c, Point d, float t){
	return ((-1*a + 3*b - 3*c + d)*(3*t*t)) +
					((3*a - 6*b + 3*c)*(2*t)) +
					(-3*a + 3*b);
}

void BezierCurve::calculateParameterizedPoints() {
	int number_of_points = 1000;
	float distance_step = calculateLength() / (float)number_of_points;
	float resolution = 10000;

	float distance_since_last = 0.0f;

	Point last_point = getPointFromT(0);
	addParameterizedPoint(last_point);

	for (int n = 0; n < resolution; ++n) {

		float t = ((float)n) / (float)resolution;
		t *= getMaximumT();

		Point current_point = getPointFromT(t);

		float distance_to_last = Vector3(current_point, last_point).magnitude();
		distance_since_last += distance_to_last;

		if (distance_since_last >= distance_step) {
			addParameterizedPoint(current_point);
			distance_since_last = 0;
		}

		last_point = current_point;
	}

	addParameterizedPoint(last_point);
}

float BezierCurve::calculateLength() {
	float length = 0;
	Point last_point = getPointFromT(0);

	float resolution = 1000;

	for (int n = 0; n < resolution; ++n) {

		float t = ((float)n) / (float)resolution;
		t *= getMaximumT();

		Point current_point = getPointFromT(t);

		float distance_to_last = Vector3(current_point, last_point).magnitude();
		length += distance_to_last;


		last_point = current_point;
	}

	return length;
}

void BezierCurve::addParameterizedPoint(Point& point) {
	parameterized_points.push_back(point);
}

Point BezierCurve::getControlPoint(int index) {
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
