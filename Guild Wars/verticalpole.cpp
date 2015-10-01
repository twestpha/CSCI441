#include "verticalpole.h"
#include "drawable.h"

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

VerticalPole::VerticalPole(float x, float y, float z) : Drawable(x, y, z){
}

void VerticalPole::draw(){
	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 2.0, z);
	    glScalef(1.0, 6.0, 1.0);
	    glColor3f(r, g, b);
	    glutSolidCube(0.5);
    glPopMatrix();
}