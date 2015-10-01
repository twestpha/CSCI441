#include "Drawable.hpp"
#include "Fuselage.hpp"
#include "Hero.hpp"
#include "VerticalPole.hpp"
#include "HorizontalPole.hpp"
#include "Rotor.hpp"
#include "Propeller.hpp"

#ifndef vehicle_h
#define vehicle_h

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
