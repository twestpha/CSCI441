#include "BezierPatchDrawer.hpp"

BezierPatchDrawer::BezierPatchDrawer(BezierPatch& bezier_patch) : bezier_patch(bezier_patch){

    control_cage_is_visible = false;
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
    for(int u(0); u < resolution + 1; ++u){
        for(int v(0); v < resolution + 1; ++v){
            // Iterate from 0, 0 to T_u, T_v
            float T_u = float(u)/float(resolution);
            float T_v = float(v)/float(resolution);

            patch_vertices.push_back(bezier_patch.getPointFromUV(T_u, T_v));

            Point a = bezier_patch.getPointFromUV(T_u, T_v);
            Point b = bezier_patch.getPointFromUV(T_u + 0.01, T_v);
            Point c = bezier_patch.getPointFromUV(T_u, T_v + 0.01);

            Vector3 ab(a, b);
            Vector3 ac(a, c);
            Vector3 normal = ac.cross(ab).unit();

            patch_normals.push_back(normal);
        }
    }
}

void BezierPatchDrawer::renderPatch(){
    Material patch_material(Color(0.27, 0.24, 0.14), Color(), Color());
    patch_material.apply();
    for(unsigned int i(0); i < patch_vertices.size() - getDefaultResolution() - 2; ++i){

        Point a = patch_vertices[i];
        Point b = patch_vertices[i + 1];
        Point c = patch_vertices[i + getDefaultResolution() + 1];
        Point d = patch_vertices[i + getDefaultResolution() + 2];

        Vector3 normal_a = patch_normals[i];
        Vector3 normal_b = patch_normals[i + 1];
        Vector3 normal_c = patch_normals[i + getDefaultResolution() + 1];
        Vector3 normal_d = patch_normals[i + getDefaultResolution() + 2];

        glBegin(GL_QUADS);
            glNormal3f(normal_a.x, normal_a.y, normal_a.z);
            glVertex3f(a.getX(), a.getY(), a.getZ());

            glNormal3f(normal_b.x, normal_b.y, normal_b.z);
            glVertex3f(b.getX(), b.getY(), b.getZ());

            glNormal3f(normal_d.x, normal_d.y, normal_d.z);
            glVertex3f(d.getX(), d.getY(), d.getZ());

            glNormal3f(normal_c.x, normal_c.y, normal_c.z);
            glVertex3f(c.getX(), c.getY(), c.getZ());
        glEnd();

    }
}

void BezierPatchDrawer::renderControlCage() {
    glDisable(GL_LIGHTING);
    for(int i(0); i < bezier_patch.getNumberOfPoints(); ++i){

        PointDrawer point_drawer(bezier_patch.getPointAtIndex(i));
        point_drawer.draw();
    }
    glEnable(GL_LIGHTING);
}
