#include "BezierTrack.hpp"

#include "BezierCurveDrawer.hpp"

BezierTrack::BezierTrack(BezierCurve curve): curve(move(curve)) {
    generateTrackGeometry();
}

void BezierTrack::draw(){
    Material track_material(Color(0.48, 0.42, 0.32), Color(), Color());
    track_material.apply();

    for(unsigned int i(0); i < points.size() - 2; i+=2){
        glBegin(GL_QUADS);
            Point a = points[i];
            Point b = points[i + 1];
            Point c = points[i + 2];
            Point d = points[i + 3];

            Vector3 ab(a, b);
            Vector3 ac(a, c);
            Vector3 normal = ac.cross(ab).unit();

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(a.getX(), a.getY(), a.getZ());

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(b.getX(), b.getY(), b.getZ());

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(d.getX(), d.getY(), d.getZ());

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(c.getX(), c.getY(), c.getZ());
        glEnd();
    }

}

void BezierTrack::generateTrackGeometry(){
    for(int i(0); i < getDefaultResolution() + 1; ++i){
        // get the point and the normal at t of the curve
        float t = float(i)/float(getDefaultResolution() + 1);
        Point p = curve.getPointFromS(t);
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
    return 100;
}

BezierCurve& BezierTrack::getCurve() {
    return curve;
}

Point BezierTrack::getPointFromT(float t){
    return curve.getPointFromT(t);
}

Vector3 BezierTrack::getTangentFromT(float t) {
    return curve.getTangentFromT(t);
}
