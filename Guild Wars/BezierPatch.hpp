#ifndef bezier_patch_h
#define bezier_patch_h

#include <vector>

#include "Point.hpp"
#include "BezierCurve.hpp"
#include "BezierCurveDrawer.hpp"

class BezierPatch{
public:
    BezierPatch(std::vector<Point> input_points);

    int getNumberOfControlCurves();
    BezierCurve& getCurveAtIndex(int index);

    Point getPointFromUV(float u, float v);
    Point interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t);
private:
    std::vector<Point> control_points;
};

#endif
