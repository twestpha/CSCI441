#ifndef BezierCurveDrawer_h
#define BezierCurveDrawer_h

#include "BezierCurve.hpp"
#include "Vector3.hpp"

class BezierCurveDrawer {
public:
    BezierCurveDrawer(BezierCurve& bezier_curve);

    void toggleControlCageVisibility();
	void toggleCurveVisibility();

	bool isCurveVisible(){ return curveIsVisible; }
	bool isControlCageVisible(){ return controlCageIsVisible; }

    void render();
    void render(int resolution);
    void renderControlPoints();

private:

    bool controlCageIsVisible;
	bool curveIsVisible;

    BezierCurve& bezier_curve;

};

#endif
