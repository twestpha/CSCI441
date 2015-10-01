#include "drawable.h"
#include "fuselage.h"
#include "hero.h"
#include "verticalpole.h"
#include "horizontalpole.h"
#include "rotor.h"
#include "propeller.h"

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
