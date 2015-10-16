#ifndef BezierCurveDrawer_h
#define BezierCurveDrawer_h

#include "BezierCurve.hpp"
#include "Vector3.hpp"
#include "PointDrawer.hpp"

class BezierCurveDrawer {
public:
    BezierCurveDrawer(BezierCurve& bezier_curve);

    void toggleControlCageVisibility();
	void toggleCurveVisibility();

	bool isCurveVisible(){ return curve_is_visible; }
	bool isControlCageVisible(){ return control_cage_is_visible; }

    void draw();
    void draw(int resolution);

private:

    int getDefaultResolution();

    void renderCurve(int resolution);
    void renderControlPoints();

    BezierCurve& getCurve();

    bool control_cage_is_visible;
	bool curve_is_visible;

    BezierCurve& bezier_curve;

};

#endif
