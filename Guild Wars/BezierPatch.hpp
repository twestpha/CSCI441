#ifndef bezier_patch_h
#define bezier_patch_h

#include <vector>

#include "Point.hpp"
#include "BezierCurve.hpp"

class BezierPatch{
public:
    BezierPatch(std::vector<Point> control_points);
    void draw();
private:
    std::vector<BezierCurve> control_points;
};

#endif
