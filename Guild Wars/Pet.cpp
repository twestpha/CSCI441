#include "Pet.hpp"
#include "Drawable.hpp"
#include "BezierCurve.hpp"
#include "Point.hpp"

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

Pet::Pet(float x, float y, float z) : Drawable(x, y, z), w(x, y, z){
    t = 0.0;
    w.setColor(0.0, 0.0, 1.0);
}

void Pet::draw(BezierCurve &b){
    Point p = b.getPointFromT(t);
    x = p.getX();
    y = p.getY();
    z = p.getZ();

    t+=0.005;
    if(t > 1.0){
        t = 0.0;
    }

    glPushMatrix();
	    glTranslatef(x, y, z);

        glColor3f(1.0, 1.0, 0.0);
        glutSolidCube(1);
        w.draw();

    glPopMatrix();
}
