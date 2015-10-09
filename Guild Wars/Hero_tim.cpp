#include "Hero_tim.hpp"

void Hero_tim::draw()
{
	glColor3f(1, 0, 0);
	float col[4] = { 1, 0, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);



	glPushMatrix(); {
		tansform.apply();


		glPushMatrix(); {

			drawCloak();
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 5, 0);
			drawTorso();
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 9.5, 0);
			drawHead();
		}glPopMatrix();
	}glPopMatrix();
}

void Hero_tim::updateAnimation()
{
	if (armAngle < 0 || armAngle > 120) {
		armFlag = !armFlag;
	}
	if (armFlag) {
		armAngle += 1;
	}
	else {
		armAngle -= 1;
	}
}

void Hero_tim::drawCloak()
{
	glColor3f(1, 0, 1);
	float col[4] = {1, 0, 1, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix(); {
		glTranslatef(0, -2.5, 0);
		glRotatef(90, -1, 0, 0);
		glScalef(1, 0.5, 1);
		glutSolidCone(3, 10, 100, 100);
	}glPopMatrix();

}

void Hero_tim::drawTorso()
{
	glColor3f(1, 0, 0);
	float col[4] = { 1, 0, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);


	glPushMatrix(); {


		//draw right arm
		glPushMatrix(); {
			glTranslatef(2.5, 3, 0);
			glRotatef(armAngle, -1, 0, 0);
			drawArm();
			drawStaff();
		}glPopMatrix();

		//draw left arm
		glPushMatrix(); {
			glTranslatef(-2.5, 3, 0);
			drawArm();
		}glPopMatrix();

		//draw torso
		glScalef(2, 3, 1);
		glutSolidCube(2);
	}glPopMatrix();
}

void Hero_tim::drawArm()
{
	glColor3f(1, 0, 1);
	float col[4] = { 1, 0, 1, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix(); {
		glTranslatef(0, -2, 0);
		glPushMatrix(); {
			glTranslatef(0, -0.5, 0);
			glScalef(1, 5, 1);
			glutSolidCube(1);
		}glPopMatrix();
		glColor3f(1, 0.5, 0.5);
		glPushMatrix(); {
			glTranslatef(0, -3, 0);
			glutSolidSphere(1.0, 100, 100);
		}glPopMatrix();
	}glPopMatrix();
}

void Hero_tim::drawStaff()
{
	glColor3f(0.3, 0.15, 0);
	float col[4] = { 0.3, 0.15, 0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix(); {
		glTranslatef(0, -5, 0);
		glPushMatrix(); {
			glTranslatef(0, 0, -2);
			glScalef(0.5, 0.5, 10);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0, 3);
			glutSolidSphere(0.75, 100, 100);
		}glPopMatrix();
	}glPopMatrix();
}

void Hero_tim::drawHead()
{
	glColor3f(1, 0.5, 0.5);
	float col[4] = { 1, 0.5, 0.5 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix(); {
		glutSolidSphere(1.5, 100, 100);
	}glPopMatrix();
}

