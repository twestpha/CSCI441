#include "Flag.hpp"

Flag::Flag(float x, float y, float z) : Drawable(x, y, z){
}

void Flag::draw(){
	Material pole_material(Color(0.3, 0.3, 0.3, 1), Color(), Color());
	pole_material.apply();
	glPushMatrix();
	    glTranslatef(x, y + 4.5, z);
	    glScalef(0.1, 9.0, 0.1);
	    glutSolidCube(1);
    glPopMatrix();

	Material flag_material(Color(0.9, 0.1, 0.1, 1), Color(), Color());
	flag_material.apply();
    glPushMatrix();
	    glTranslatef(x, y + 7.0, z);
	    // glRotatef(-90, 1.0, 0.0, 0.0);
		glScalef(0.1, 1.0, 1.0);
	    glutSolidCone(2.0, 6.0, 16, 1);
    glPopMatrix();
}
