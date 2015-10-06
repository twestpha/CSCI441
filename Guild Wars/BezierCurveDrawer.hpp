#ifndef BezierCurveDrawer_h
#define BezierCurveDrawer_h

#include "BezierCurve.hpp"
#include "Vector3.hpp"

class BezierCurveDrawer {
public:
    BezierCurveDrawer(BezierCurve& bezier_curve);

    void render();
    void render(int resolution);
    void renderControlPoints();

private:

    BezierCurve& bezier_curve;

};

#endif
