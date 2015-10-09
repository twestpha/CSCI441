#pragma once


class Hero_tim : HeroBase {
public:
	float armAngle;
	bool armAngle;
	
	void draw();
	void updateAnimation();

	void drawCloak();
	void drawTorso();
	void drawArm();
	void drawStaff();
	void drawHead();
};