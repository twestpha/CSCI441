#include "Tree.hpp"

Tree::Tree(float x, float y, float z) : Drawable(x, y, z){
}

void Tree::draw(){
	Material trunk_material(Color(0.5, 0.2, 0.0, 1), Color(), Color());
	trunk_material.apply();
	glPushMatrix();
	    glTranslatef(x, y, z);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glutSolidCone(1.0, 4.0, 16, 1);
    glPopMatrix();

	Material tree_material(Color(0.1, 0.8, 0.1, 1), Color(), Color());
	tree_material.apply();
    glPushMatrix();
	    glTranslatef(x, y + 2.0, z);
	    glRotatef(-90, 1.0, 0.0, 0.0);
	    glutSolidCone(2.0, 6.0, 16, 1);
    glPopMatrix();
}
