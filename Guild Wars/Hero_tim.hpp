#ifndef hero_tim_h
#define hero_tim_h

#include <iostream>

#include "math_safe.hpp"

#include "HeroBase.hpp"
#include "BezierPatch.hpp"

using namespace std;

class Hero_tim : public HeroBase {
public:
	Hero_tim(Transform3D transform, BezierPatch* patch);

	void draw();
	void updateAnimation();

	void turnRight();		//Adds rotation to transform rotation axis
	void turnLeft();

	void moveForward();
	void moveBackward();

	void setBezierPatch(BezierPatch* patch);

private:

	float armAngle;
	bool armFlag;
	float theta;
	float dirX;		//direction X
	float dirZ;		//direction Z
	float u;
	float v;
	BezierPatch* patch;

	float getU();
	float getV();
	Point getCurrentPoint();
	Vector3 getCurrentTangent();
	void ensureInBounds();
	void moveToCurrentPoint();

	BezierPatch& getPatch();
	void drawCloak();
	void drawTorso();
	void drawArm();
	void drawStaff();
	void drawHead();

	void computeDirection();	//uses theta to calculate direction vector
};
#endif
