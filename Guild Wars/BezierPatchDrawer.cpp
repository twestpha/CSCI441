#include "BezierPatchDrawer.hpp"

BezierPatchDrawer::BezierPatchDrawer(BezierPatch& bezier_patch) : bezier_patch(bezier_patch){

    control_cage_is_visible = true;
    patch_is_visible = true;

    generatePatchVertices(getDefaultResolution());
}

int BezierPatchDrawer::getDefaultResolution() {
    return 100;
}

void BezierPatchDrawer::draw() {
    if (patch_is_visible) {
        renderPatch();
    }
    if (control_cage_is_visible) {
        renderControlCage();
    }
}

void BezierPatchDrawer::toggleControlCageVisibility(){
	control_cage_is_visible=!control_cage_is_visible;
}

void BezierPatchDrawer::togglePatchVisibility(){
	patch_is_visible=!patch_is_visible;
}

void BezierPatchDrawer::generatePatchVertices(int resolution){
    for(int u(0); u < resolution; ++u){
        for(int v(0); v < resolution; ++v){
            // Iterate from 0, 0 to T_u, T_v
            float T_u = float(u)/float(resolution);
            float T_v = float(v)/float(resolution);

            patch_vertices.push_back(bezier_patch.getPointFromUV(T_u, T_v));
        }
    }
}

void BezierPatchDrawer::renderPatch() {
    // draw stuff
    //patch_vertices 
}

void BezierPatchDrawer::renderControlCage() {  
    // something else
}
