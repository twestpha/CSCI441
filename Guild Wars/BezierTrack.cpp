#include "BezierTrack.hpp"

BezierTrack::BezierTrack(BezierCurve& curve): curve(curve) {
    generateTrackGeometry();
}

void BezierTrack::draw(){

}

void BezierTrack::generateTrackGeometry(){
    for(int i(0); i < getDefaultResolution() + 1; ++i){
        // get the point and the normal at t of the curve 
    }
}

int BezierTrack::getDefaultResolution(){
    return 10;
}