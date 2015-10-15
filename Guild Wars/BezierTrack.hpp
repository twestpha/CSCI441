#ifndef BezierTrack_h
#define BezierTrack_h

#include <vector>

#include "BezierCurve.hpp"
#include "Point.hpp"
#include "Material.hpp"
#include "Vector3.hpp"

using namespace std;

class BezierTrack{
public:
    BezierTrack(BezierCurve& curve);

    void draw();
    Point getPointFromT(float t);
private:
    void generateTrackGeometry();
    int getDefaultResolution();
    std::vector<Point> points;
    BezierCurve curve;
};

#endif
