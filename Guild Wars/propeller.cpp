#include "Propeller.hpp"
#include "Drawable.hpp"

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

Propeller::Propeller(float x, float y, float z) : Drawable(x, y, z){
	rotation = 0;
}

void Propeller::moving(){
	rotation+=27;
}

void Propeller::draw(){
	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 1.0, z - 2.0);
	    glRotatef(rotation, 0.0, 0.0, 1.0);
	    glScalef(5.0, 1.0, 1.0);
	    
	    glColor3f(r, g, b);
	    glutSolidCube(0.5);
    glPopMatrix();
}