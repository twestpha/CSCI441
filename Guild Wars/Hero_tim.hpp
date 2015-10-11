#pragma once
#include "HeroBase.hpp"

using namespace std;

class Hero_tim : public HeroBase {
public:
	Hero_tim(Transform3D transform) : HeroBase(transform) { ; }

	float armAngle;
	bool armFlag;
	
	void draw();
	void updateAnimation();

	void drawCloak();
	void drawTorso();
	void drawArm();
	void drawStaff();
	void drawHead();
};