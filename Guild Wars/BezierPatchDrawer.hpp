#ifndef BezierPatchDrawer_h
#define BezierPatchDrawer_h

#include "BezierPatch.hpp"
#include "Vector3.hpp"
#include "PointDrawer.hpp"

class BezierPatchDrawer {
public:
    BezierPatchDrawer(BezierPatch& bezier_patch);

    void toggleControlCageVisibility();
	void togglePatchVisibility();

	bool isPatchVisible(){ return patch_is_visible; }
	bool isControlCageVisible(){ return control_cage_is_visible; }

    void draw();
    void draw(int resolution);

private:

    int getDefaultResolution();

    void renderPatch(int resolution);
    void renderControlPoints();

    bool control_cage_is_visible;
	bool patch_is_visible;

    BezierPatch& bezier_patch;

};

#endif
