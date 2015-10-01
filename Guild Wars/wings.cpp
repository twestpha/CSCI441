#include "Wings.hpp"
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

Wings::Wings(float x, float y, float z) : Drawable(x, y, z){
	rotation = 0;
}

void Wings::draw(){
	rotation+=5;

	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 0.75, z);
	    glRotatef(rotation, 0.0, 1.0, 0.0);
	    glScalef(1.0, 1.0, 5.0);

	    glColor3f(r, g, b);
	    glutSolidCube(0.5);
    glPopMatrix();
}
