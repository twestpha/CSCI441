#ifndef hero_tim_h
#define hero_tim

#include "HeroBase.hpp"
#include <math.h>

using namespace std;

class Hero_tim : public HeroBase {
public:
	Hero_tim(Transform3D transform) : HeroBase(transform) { ; }

	float armAngle;
	bool armFlag;
	float theta;
	float dirX;		//direction X
	float dirZ;		//direction Z
	
	void draw();
	void updateAnimation();

	void drawCloak();
	void drawTorso();
	void drawArm();
	void drawStaff();
	void drawHead();

	void turnRight();		//Adds rotation to transform rotation axis
	void turnLeft();		
	void computeDirection();	//uses theta to calculate direction vector
};
#endif