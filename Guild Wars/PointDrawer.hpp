#ifndef PointDrawer_h
#define PointDrawer_h

#include "Point.hpp"
#include "gl_includes.hpp"
#include "Vector3.hpp"

class PointDrawer {
public:
    PointDrawer(Point& point);

    void draw();
    static void drawLineBetween(Point& p0, Point& p1, float thickness, Vector3 color);

    Point& getPoint();

private:

    Point& point;
};

#endif
