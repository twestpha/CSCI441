#ifndef vehicle_h
#define vehicle_h

#include <algorithm>

#include "Drawable.hpp"
#include "Fuselage.hpp"
#include "Hero.hpp"
#include "VerticalPole.hpp"
#include "HorizontalPole.hpp"
#include "Rotor.hpp"
#include "Propeller.hpp"

#include "math_safe.hpp"
#include "gl_includes.hpp"

class Vehicle : public Drawable {
public:
	Vehicle(float x, float y, float z);
	void draw();
	void driveForward();
	void driveBackward();
	void turnRight();
	void turnLeft();
	void clampMovement();
	int getRotation(){return rotation; }
private:
	int rotation;
	Fuselage fuselage;
	Hero hero;
	VerticalPole vertical_pole;
	HorizontalPole horizontal_pole;
	Rotor rotor;
	Propeller propeller;
};

#endif
