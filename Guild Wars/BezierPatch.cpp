#include "BezierPatch.hpp"

#include <vector>
#include <stdlib.h>

#include "BezierCurve.hpp"

const int NUMBER_OF_POINTS = 16;

BezierPatch::BezierPatch(std::vector<Point> input_points){
    // Control Point specification - Left to Right, Top to Bottom
    // 0 1 2 3
    // 4 5 6 7
    // 8 9 0 1
    // 2 3 4 5

    if(input_points.size() != NUMBER_OF_POINTS){
        printf("Incorrect number of control points. Given: %d, Required: 16\n", int(input_points.size()));
        exit(1);
    }

    control_points = input_points;
}

int BezierPatch::getNumberOfPoints(){
    return 16;
}

Point& BezierPatch::getPointAtIndex(int index){
    return control_points[index];
}

Point BezierPatch::getPointFromUV(float u, float v){
    return interpolatePointFromCurveAlongT(
        interpolatePointFromCurveAlongT(control_points[0], control_points[1], control_points[2], control_points[3], u),
        interpolatePointFromCurveAlongT(control_points[4], control_points[5], control_points[6], control_points[7], u),
        interpolatePointFromCurveAlongT(control_points[8], control_points[9], control_points[10], control_points[11], u),
        interpolatePointFromCurveAlongT(control_points[12], control_points[13], control_points[14], control_points[15], u),
        v
    );
}

Vector3 BezierPatch::getTangentFromUV(float u, float v){
    Point p = interpolateTangentPointFromCurveAlongT(
        interpolateTangentPointFromCurveAlongT(control_points[0], control_points[1], control_points[2], control_points[3], u),
        interpolateTangentPointFromCurveAlongT(control_points[4], control_points[5], control_points[6], control_points[7], u),
        interpolateTangentPointFromCurveAlongT(control_points[8], control_points[9], control_points[10], control_points[11], u),
        interpolateTangentPointFromCurveAlongT(control_points[12], control_points[13], control_points[14], control_points[15], u),
        v
    );
    return Vector3(p.getX(), p.getY(), p.getZ());
}

Point BezierPatch::interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t){
    return ((-1*a + 3*b - 3*c + d)*(t*t*t)) +
                    ((3*a - 6*b + 3*c)*(t*t)) +
                    ((-3*a + 3*b)*(t)) +
                    (a);
}

Point BezierPatch::interpolateTangentPointFromCurveAlongT(Point a, Point b, Point c, Point d, float t){
    return ((-1*a + 3*b - 3*c + d)*3*(t*t)) +
                    ((3*a - 6*b + 3*c)*2*t) +
                    (-3*a + 3*b);
}
