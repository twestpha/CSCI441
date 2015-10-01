#include "Fuselage.hpp"
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

Fuselage::Fuselage(float x, float y, float z) : Drawable(x, y, z){
}

void Fuselage::draw(){
	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 1.0, z);
	    glScalef(1.0, 0.1, 1.0);
	    glColor3f(r, g, b);
	    glutSolidCone(2.0, 2.0, 8, 1);
    glPopMatrix();
}
