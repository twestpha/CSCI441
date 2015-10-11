#include "BezierPatchDrawer.hpp"

BezierPatchDrawer::BezierPatchDrawer(BezierPatch& bezier_patch) : bezier_patch(bezier_patch){

    control_cage_is_visible = true;
    patch_is_visible = true;

    generatePatchVertices(getDefaultResolution());
}

int BezierPatchDrawer::getDefaultResolution() {
    return 10;
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

void BezierPatchDrawer::renderPatch(){
    glColor3f(1.0f, 0.0f, 0.0f);
    for(unsigned int i(0); i < patch_vertices.size() - getDefaultResolution() - 1; ++i){
        if((i + 1) % getDefaultResolution() != 0){
            Point a = patch_vertices[i];
            Point b = patch_vertices[i + 1];
            Point c = patch_vertices[i + getDefaultResolution()];
            Point d = patch_vertices[i + getDefaultResolution() + 1];
            glBegin(GL_QUADS);
                glVertex3f(a.getX(), a.getY(), a.getZ());
                glVertex3f(b.getX(), b.getY(), b.getZ());
                glVertex3f(d.getX(), d.getY(), d.getZ());
                glVertex3f(c.getX(), c.getY(), c.getZ());
            glEnd();
        }
    }
}

void BezierPatchDrawer::renderControlCage() {  
    // something else
}
