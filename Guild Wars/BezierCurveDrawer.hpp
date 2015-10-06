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

	bool isCurveVisible(){ return curveIsVisible; }
	bool isControlCageVisible(){ return controlCageIsVisible; }

    void draw();
    void draw(int resolution);

private:

    int getDefaultResolution();

    void renderCurve(int resolution);
    void renderControlPoints();

    bool controlCageIsVisible;
	bool curveIsVisible;

    BezierCurve& bezier_curve;

};

#endif
