#include "BezierPatch.hpp"

#include <vector>

#include "BezierCurve.hpp"

const int POINTS_PER_CURVE = 4;
const int NUMBER_OF_CONTROL_CURVES = 8;

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

    std::vector<Point> temp_column;
    std::vector<Point> temp_row;

    control_curves.reserve(NUMBER_OF_CONTROL_CURVES);

    for(int i(0); i < POINTS_PER_CURVE; ++i){
        temp_column.clear();
        temp_row.clear();

        for(int j(0); j < POINTS_PER_CURVE; ++j){
            temp_column.push_back(input_points[(i*POINTS_PER_CURVE)+j]);
            temp_row.push_back(input_points[i+(j*POINTS_PER_CURVE)]);
        }

        control_curves[i] = BezierCurve(temp_column);
        control_curves[i+POINTS_PER_CURVE] = BezierCurve(temp_row);
    }
}

void BezierPatch::draw(){

}
