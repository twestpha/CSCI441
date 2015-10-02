#include "Tree.hpp"

Tree::Tree(float x, float y, float z) : Drawable(x, y, z){
}

void Tree::draw(){
	glPushMatrix();
	    glTranslatef(x, y, z);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glColor3f(0.5, 0.2, 0.0);
	    glutSolidCone(1.0, 4.0, 16, 1);
    glPopMatrix();

    glPushMatrix();
	    glTranslatef(x, y + 2.0, z);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glColor3f(0.1, 0.8, 0.1);
	    glutSolidCone(2.0, 6.0, 16, 1);
    glPopMatrix();
}
