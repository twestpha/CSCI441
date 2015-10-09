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
private:
    std::vector<BezierCurve> control_curves;
};

#endif
