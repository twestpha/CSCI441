#ifndef BezierPatchDrawer_h
#define BezierPatchDrawer_h

#include "BezierPatch.hpp"
#include "Vector3.hpp"
#include "PointDrawer.hpp"
#include "Material.hpp"

class BezierPatchDrawer {
public:
    BezierPatchDrawer(BezierPatch& bezier_patch);

    void toggleControlCageVisibility();
    void togglePatchVisibility();

    bool isPatchVisible(){ return patch_is_visible; }
    bool isControlCageVisible(){ return control_cage_is_visible; }

    void draw();

private:

    int getDefaultResolution();

    void renderPatch();
    void renderControlCage();

    void generatePatchVertices(int resolution);

    bool control_cage_is_visible;
    bool patch_is_visible;

    BezierPatch& bezier_patch;
    std::vector<Point> patch_vertices;
    std::vector<Vector3> patch_normals;

};

#endif
