#include "vehicle.h"

#include <math.h>
// For some reason, math.h isn't including constants - maybe an old version on the machine I'm compiling on...
#define M_PI 3.141592654

#include <algorithm>

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

Vehicle::Vehicle(float x, float y, float z) : Drawable(x, y, z), fuselage(x, y, z), hero(x, y, z), vertical_pole(x, y, z), horizontal_pole(x, y, z), rotor(x, y, z), propeller(x, y, z){
	fuselage.setColor(1.0, 0.0, 0.0);
	hero.setColor(1.0, 1.0, 0.0);
	vertical_pole.setColor(0.5, 0.2, 0.0);
	horizontal_pole.setColor(0.5, 0.2, 0.0);
	rotor.setColor(0.5, 0.5, 0.5);
	propeller.setColor(0.5, 0.5, 0.5);

	rotation = 0;
}

void Vehicle::draw(){
	glPushMatrix();
	    glTranslatef(x, y, z);
	    glRotatef(rotation, 0.0, 1.0, 0.0);
	    fuselage.draw();
	    hero.draw();
	    vertical_pole.draw();
	    horizontal_pole.draw();
	    rotor.draw();

	    propeller.draw();
    glPopMatrix();
}

void Vehicle::driveForward(){
	float theta = rotation * M_PI / 180.0;
	z += 0.25 * cos(theta);
	x += 0.25 * sin(theta);
	clampMovement();
	propeller.moving();
}

void Vehicle::driveBackward(){
	float theta = rotation * M_PI / 180.0;
	z -= 0.25 * cos(theta);
	x -= 0.25 * sin(theta);
	clampMovement();
	propeller.moving();
}

void Vehicle::turnRight(){
	rotation -= 5;
}

void Vehicle::turnLeft(){
	rotation += 5;
}

void Vehicle::clampMovement(){
	x = std::max(-50.0f, std::min(x, 50.0f));
	z = std::max(-50.0f, std::min(z, 50.0f));
}
