#ifndef BezierTrack_h
#define BezierTrack_h

#include "BezierCurve.hpp"
#include "Point.hpp"
#include <vector>

class BezierTrack{
public: 
    BezierTrack(BezierCurve& curve);

    void draw();
private:
    void generateTrackGeometry();
    int getDefaultResolution();
    std::vector<Point> points;
    BezierCurve curve;
};

#endif