#include "BezierPatchDrawer.hpp"

BezierPatchDrawer::BezierPatchDrawer(BezierPatch& bezier_Patch) : bezier_patch(bezier_patch){

    control_cage_is_visible = true;
    curve_is_visible = true;

}

void BezierPatchDrawer::draw() {
    draw(getDefaultResolution());
}

int BezierPatchDrawer::getDefaultResolution() {
    return 100;
}

void BezierPatchDrawer::draw(int resolution) {
    if (curve_is_visible) {
        renderPatch(resolution);
    }
    if (control_cage_is_visible) {
        // renderControlPoints();
    }
}


void BezierPatchDrawer::toggleControlCageVisibility(){
	control_cage_is_visible=!control_cage_is_visible;
}

void BezierPatchDrawer::toggleCurveVisibility(){
	curve_is_visible=!curve_is_visible;
}

void BezierPatchDrawer::renderPatch(int resolution) {
    // This function does things

    
}

void BezierPatchDrawer::renderControlPoints() {
    // Iunno. something.
}
