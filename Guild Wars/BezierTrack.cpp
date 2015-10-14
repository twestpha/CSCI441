#include "BezierTrack.hpp"

BezierTrack::BezierTrack(BezierCurve& curve): curve(curve) {
    generateTrackGeometry();
}

void BezierTrack::draw(){
    glDisable(GL_LIGHTING);
    for(unsigned int i(1); i < points.size(); ++i){
        glBegin(GL_LINES);
            Point a = points[i-1];
            Point b = points[i];

            glVertex3f(a.getX(), a.getY(), a.getZ());
            glVertex3f(b.getX(), b.getY(), b.getZ());
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

void BezierTrack::generateTrackGeometry(){
    for(int i(0); i < getDefaultResolution() + 1; ++i){
        // get the point and the normal at t of the curve 
        float t = float(i)/float(getDefaultResolution() + 1);
        Point p = curve.getPointFromT(t);
        Vector3 v = curve.getTangentFromT(t);

        Vector3 l = v.cross(Vector3::up());
        Vector3 r = Vector3::up().cross(v);

        Point left_point = Point(p.getX() + l.x, p.getY() + l.y, p.getZ() + l.z);
        Point right_point = Point(p.getX() + r.x, p.getY() + r.y, p.getZ() + r.z);

        points.push_back(left_point);
        points.push_back(right_point);
    }
}

int BezierTrack::getDefaultResolution(){
    return 10;
}