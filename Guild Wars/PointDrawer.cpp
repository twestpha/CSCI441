#include "PointDrawer.hpp"

PointDrawer::PointDrawer(Point& point) : point(point) {

}

void PointDrawer::drawLineBetween(Point& point1, Point& point2, float thickness, Vector3 color) {

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

void PointDrawer::draw() {
	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(getPoint().getX(), getPoint().getY(), getPoint().getZ());
		glScalef(0.25, 0.25, 0.25);
		glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

Point& PointDrawer::getPoint() {
    return point;
}
