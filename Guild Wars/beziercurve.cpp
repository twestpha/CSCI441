#include "beziercurve.h"
#include "point.h"

#include <stdio.h>

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

BezierCurve::BezierCurve(){
	controlCageIsVisible = false;
	curveIsVisible = false;
}

void BezierCurve::addPoint(Point p){
	points.push_back(p);
}

void BezierCurve::draw(int resolution){
	if(controlCageIsVisible){
		drawPoints();
		drawControlCage();
	}
	if(curveIsVisible){
		drawCurve(resolution);
	}
}

void BezierCurve::toggleControlCageVisibility(){
	controlCageIsVisible=!controlCageIsVisible;
}

void BezierCurve::toggleCurveVisibility(){
	curveIsVisible=!curveIsVisible;
}

void BezierCurve::drawPoints(){
	for(unsigned int i(0); i < points.size(); ++i){
		glPushMatrix();
			// Translate our sphere
			Point p = points[i];
	    	glTranslatef(p.getX(), p.getY(), p.getZ());

	    	// Draw the sphere for the point itself
	    	glColor3f(0.0, 1.0, 0.0);
	    	glutSolidSphere(0.5, 16, 16);
	    glPopMatrix();
	}
}

void BezierCurve::drawControlCage(){
	glDisable( GL_LIGHTING );

	for(unsigned int j(1); j < points.size(); ++j){
		Point a = points[j];
		Point b = points[j - 1];

		glColor3f(1.0, 1.0, 0.0);
    	glLineWidth(3.0);

    	glBegin(GL_LINES);
   	 		glVertex3f(a.getX(), a.getY(), a.getZ());
    		glVertex3f(b.getX(), b.getY(), b.getZ());
    	glEnd();
	}

	glEnable( GL_LIGHTING );
}

void BezierCurve::drawCurve(int resolution){

	if( (points.size() - 4) % 3 != 0 || points.size() < 4){
		printf("Wrong number of control points.\n");
		exit(1);
	}

	glDisable( GL_LIGHTING );

	Point lastPoint = points.front();
	Point nextPoint;

	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(1.0);

	// First, let's get the number of "chunks" of 4 points we need
	for( unsigned int i(3); i < points.size(); i+=3){
		// Chunk of 4

		Point a = points[i-3];
		Point b = points[i-2];
		Point c = points[i-1];
		Point d = points[i];

		for(int j(0); j < resolution; ++j){

			float t = float(j)/float(resolution);

			nextPoint = interpolatePointFromCurveAlongT(a, b, c, d, t);

			glBegin(GL_LINES);
				glVertex3f(lastPoint.getX(), lastPoint.getY(), lastPoint.getZ());
				glVertex3f(nextPoint.getX(), nextPoint.getY(), nextPoint.getZ());
			glEnd();

			lastPoint = nextPoint;
		}
	}

	nextPoint = points.back();
	glBegin(GL_LINES);
		glVertex3f(lastPoint.getX(), lastPoint.getY(), lastPoint.getZ());
		glVertex3f(nextPoint.getX(), nextPoint.getY(), nextPoint.getZ());
	glEnd();

	glEnable( GL_LIGHTING );
}

Point BezierCurve::getPointFromT(float t){
	// Which chunk are we on?
	int number_chunks = ((points.size() - 4) / 3) + 1;
	int which_chunk = int(float(number_chunks)*t);
	float t_per_chunk = 1.0/float(number_chunks);
	float normalized_t = t - (t_per_chunk * which_chunk);
	normalized_t/=t_per_chunk;

	Point a = points[(which_chunk*3)+0];
	Point b = points[(which_chunk*3)+1];
	Point c = points[(which_chunk*3)+2];
	Point d = points[(which_chunk*3)+3];

	return interpolatePointFromCurveAlongT(a, b, c, d, normalized_t);
}

Point BezierCurve::interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t){
	return ((-1*a + 3*b - 3*c + d)*(t*t*t)) +
					((3*a - 6*b + 3*c)*(t*t)) +
					((-3*a + 3*b)*(t)) +
					(a);
}
