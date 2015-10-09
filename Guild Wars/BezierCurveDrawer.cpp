#include "BezierCurveDrawer.hpp"

BezierCurveDrawer::BezierCurveDrawer(BezierCurve& bezier_curve) : bezier_curve(bezier_curve){

    control_cage_is_visible = true;
    curve_is_visible = true;

}

void BezierCurveDrawer::draw() {
    draw(getDefaultResolution());
}

int BezierCurveDrawer::getDefaultResolution() {
    return 100;
}

void BezierCurveDrawer::draw(int resolution) {
    if (curve_is_visible) {
        renderCurve(resolution);
    }
    if (control_cage_is_visible) {
        renderControlPoints();
    }
}


void BezierCurveDrawer::toggleControlCageVisibility(){
	control_cage_is_visible=!control_cage_is_visible;
}

void BezierCurveDrawer::toggleCurveVisibility(){
	curve_is_visible=!curve_is_visible;
}

void BezierCurveDrawer::renderCurve(int resolution) {
    // This function draws a bezier curve from a vector of points in the following form: Draw the first four points as a curve, then use the last point from the last curve as the first point of the next curve.x

    Point last_point = bezier_curve.getPointFromT(0);
    for (int n = 0; n < resolution; ++n) {

        float t = ((float)n) / (float)resolution;
        t *= bezier_curve.getMaximumT();

        Point current_point = bezier_curve.getPointFromT(t);

        PointDrawer::drawLineBetween(last_point, current_point, 3.0, Color(0, 0, 1));

		last_point = current_point;
    }
}

void BezierCurveDrawer::renderControlPoints() {
    for (int i = 0; i < bezier_curve.getNumberOfControlPoints(); ++i) {
    	Point point = bezier_curve.getControlPoint(i);
        PointDrawer point_drawer(point);
        point_drawer.draw();

    	if (i < (bezier_curve.getNumberOfControlPoints() - 1)) {
    		Point next_point = bezier_curve.getControlPoint(i + 1);
    		PointDrawer::drawLineBetween(point, next_point, 3.0, Color(1, 1, 0));
    	}
    }

}
