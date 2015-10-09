#include "BezierPatchDrawer.hpp"

BezierPatchDrawer::BezierPatchDrawer(BezierPatch& bezier_Patch) : bezier_patch(bezier_patch){

    control_cage_is_visible = true;
    patch_is_visible = true;

}

void BezierPatchDrawer::draw() {
    draw(getDefaultResolution());
}

int BezierPatchDrawer::getDefaultResolution() {
    return 100;
}

void BezierPatchDrawer::draw(int resolution) {
    if (patch_is_visible) {
        renderPatch(resolution);
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

void BezierPatchDrawer::renderPatch(int resolution) {
    // This function does things

    
}

void BezierPatchDrawer::renderControlCage() {
    // for(unsigned int i(0); i < bezier_patch.getControlCurves.size(); ++i){
    //     BezierCurveDrawer curve_drawer(control_curves[i]);
    //     curve_drawer.draw();
    // }
}
