#include "HorizontalPole.hpp"
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

HorizontalPole::HorizontalPole(float x, float y, float z) : Drawable(x, y, z){
}

void HorizontalPole::draw(){
	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 1.0, z - 0.5);
	    glScalef(1.0, 1.0, 6.0);
	    glColor3f(r, g, b);
	    glutSolidCube(0.5);
    glPopMatrix();
}