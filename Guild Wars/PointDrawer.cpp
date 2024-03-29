#include "PointDrawer.hpp"

PointDrawer::PointDrawer(Point& point) : point(point) {

}

void PointDrawer::drawLineBetween(Point& point1, Point& point2, float thickness, Color color) {

    glDisable( GL_LIGHTING );
	glPushMatrix();
		glLineWidth(thickness);
		glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINES);
			glVertex3f(point1.getX(), point1.getY(), point1.getZ());
			glVertex3f(point2.getX(), point2.getY(), point2.getZ());
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void PointDrawer::draw() {
    Material point_material(Color(0, 0.5, 0), Color(), Color());
    point_material.apply();
    glPushMatrix();
		glTranslatef(getPoint().getX(), getPoint().getY(), getPoint().getZ());
		glScalef(0.25, 0.25, 0.25);
		glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

Point& PointDrawer::getPoint() {
    return point;
}
