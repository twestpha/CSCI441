#include "Point.hpp"

Point::Point(){
	// Empty constructor
}

Point::Point(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::drawLineBetween(Point& point1, Point& point2, float thickness, Vector3 color) {

    glDisable( GL_LIGHTING );
	glPushMatrix();
		glLineWidth(thickness);
		glColor3f(color.x, color.y, color.z);
		glBegin(GL_LINES);
			glVertex3f(point1.getX(), point1.getY(), point1.getZ());
			glVertex3f(point2.getX(), point2.getY(), point2.getZ());
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Point::draw() {
	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(getX(), getY(), getZ());
		glScalef(0.25, 0.25, 0.25);
		glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

Point operator*(Point p, float f){
	return Point(f * p.getX(), f * p.getY(), f * p.getZ());
}

Point operator*(float f, Point p){
	return p * f;
}

Point operator+(Point a, Point b){
	return Point(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Point operator-(Point a, Point b){
	return Point(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}
