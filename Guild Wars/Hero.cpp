#include "Hero.hpp"
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

Hero::Hero(float x, float y, float z) : Drawable(x, y, z){
}

void Hero::draw(){
	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 1.0, z + 0.75);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glColor3f(r, g, b);
	    glutSolidCone(0.5, 2.0, 8, 1);
    glPopMatrix();
}