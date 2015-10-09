#include "Tree.hpp"

Tree::Tree(float x, float y, float z) : Drawable(x, y, z){
}

void Tree::draw(){
	float trunk_diffuse[4] = {0.5, 0.2, 0.0, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, trunk_diffuse);
	glPushMatrix();
	    glTranslatef(x, y, z);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glutSolidCone(1.0, 4.0, 16, 1);
    glPopMatrix();

	float tree_diffuse[4] = {0.1, 0.8, 0.1, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tree_diffuse);
    glPushMatrix();
	    glTranslatef(x, y + 2.0, z);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glutSolidCone(2.0, 6.0, 16, 1);
    glPopMatrix();
}
