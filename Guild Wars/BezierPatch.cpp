#include "BezierPatch.hpp"

#include <vector>
#include <stdlib.h>

#include "BezierCurve.hpp"

const int POINTS_PER_CURVE = 4;
const int NUMBER_OF_CONTROL_CURVES = 8;
const int NUMBER_OF_POINTS = 16;

BezierPatch::BezierPatch(std::vector<Point> input_points){
    // Control Point specification - Left to Right, Top to Bottom
    // 0 1 2 3
    // 4 5 6 7
    // 8 9 0 1
    // 2 3 4 5

    // Curve Specification
    //   0 1 2 3
    // 4
    // 5
    // 6
    // 7

    if(input_points.size() != NUMBER_OF_POINTS){
        printf("Incorrect number of control points. Given: %d, Required: 16\n", int(input_points.size()));
        exit(1);
    }

    std::vector<Point> temp_column_points;
    std::vector<Point> temp_row_points;

    // vector.reserve() not working properly
    for(int i(0); i < NUMBER_OF_CONTROL_CURVES; ++i){
        control_curves.push_back(BezierCurve());
    }

    for(int i(0); i < POINTS_PER_CURVE; ++i){
        temp_column_points.clear();
        temp_row_points.clear();

        for(int j(0); j < POINTS_PER_CURVE; ++j){
            temp_column_points.push_back(input_points[(i*POINTS_PER_CURVE)+j]);
            temp_row_points.push_back(input_points[i+(j*POINTS_PER_CURVE)]);
        }

        control_curves[i] = BezierCurve(temp_column_points);
        control_curves[i+POINTS_PER_CURVE] = BezierCurve(temp_row_points);
    }
}

int BezierPatch::getNumberOfControlCurves(){
    return control_curves.size();
}

BezierCurve& BezierPatch::getCurveAtIndex(int index){
    return control_curves[index];
}
