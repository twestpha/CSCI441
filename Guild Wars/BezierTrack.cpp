#include "BezierTrack.hpp"

#include "BezierCurveDrawer.hpp"

BezierTrack::BezierTrack(BezierCurve& curve): curve(curve) {
    generateTrackGeometry();
}

void BezierTrack::draw(){
    for(unsigned int i(0); i < points.size() - 2; i+=2){
        glBegin(GL_QUADS);
            Point a = points[i];
            Point b = points[i + 1];
            Point c = points[i + 2];
            Point d = points[i + 3];

            glVertex3f(a.getX(), a.getY(), a.getZ());
            glVertex3f(b.getX(), b.getY(), b.getZ());

            glVertex3f(d.getX(), d.getY(), d.getZ());
            glVertex3f(c.getX(), c.getY(), c.getZ());
            // TODO fix normals
        glEnd();
    }
}

void BezierTrack::generateTrackGeometry(){
    for(int i(0); i < getDefaultResolution() + 1; ++i){
        // get the point and the normal at t of the curve
        float t = float(i)/float(getDefaultResolution() + 1);
        Point p = curve.getPointFromT(t);
        Vector3 v = curve.getTangentFromT(t);

        Vector3 left = v.cross(Vector3::up()).unit() * 3.0f;
        Vector3 right = Vector3::up().cross(v).unit() * 3.0f;

        Point left_point = Point(p.getX() + left.x, p.getY() + left.y, p.getZ() + left.z);
        Point right_point = Point(p.getX() + right.x, p.getY() + right.y, p.getZ() + right.z);

        points.push_back(left_point);
        points.push_back(right_point);
    }
}

int BezierTrack::getDefaultResolution(){
    return 10;
}
