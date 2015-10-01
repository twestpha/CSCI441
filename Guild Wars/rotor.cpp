#include "Rotor.hpp"
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

Rotor::Rotor(float x, float y, float z) : Drawable(x, y, z){
	rotation = 0;
}

void Rotor::draw(){
	rotation+=13;
	
	glPushMatrix();
		// Special movement goes here - scaling, movement, rotation
	    glTranslatef(x, y + 3.5, z);
	    glRotatef(rotation, 0.0, 1.0, 0.0);
	    glScalef(1.0, 1.0, 10.0);
	    
	    glColor3f(r, g, b);
	    glutSolidCube(0.5);
    glPopMatrix();
}