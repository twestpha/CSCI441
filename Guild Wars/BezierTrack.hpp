#ifndef BezierTrack_h
#define BezierTrack_h

#include <vector>
#include <iostream>

#include "BezierCurve.hpp"
#include "BezierCurveDrawer.hpp"
#include "Point.hpp"
#include "Material.hpp"
#include "Vector3.hpp"

using namespace std;

class BezierTrack{
public:
    BezierTrack(BezierCurve curve);

    void draw();
    Point getPointFromT(float t);
    Vector3 getTangentFromT(float t);

    BezierCurve& getCurve();
private:
    void generateTrackGeometry();
    int getDefaultResolution();

    vector<Point> points;
    BezierCurve curve;
};

#endif
