#include "Hero_tim.hpp"

Hero_tim::Hero_tim(Transform3D transform, BezierPatch* patch) : HeroBase(transform, "Tim the Enchanter"), patch(patch) {
	u = 0.1;
	v = 0.1;
	cout << "tim patches = " << &(getPatch()) << "\n";

}

void Hero_tim::draw()
{
	glColor3f(1, 0, 0);
	float col[4] = { 1, 0, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix(); {
		getTransform().apply();
		glTranslatef(0, 2.5, 0);
		// glRotatef(theta, 0, 1, 0);

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

void Hero_tim::setBezierPatch(BezierPatch* patch) {
	this->patch = patch;
}


void Hero_tim::updateAnimation()
{
	ensureInBounds();
	moveToCurrentPoint();

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

void Hero_tim::moveForward() {
	float r = 0.005;
	u += r * sin(theta * M_PI / 180.0f);
	v += r * cos(theta * M_PI / 180.0f);
}

void Hero_tim::moveBackward() {
	float r = 0.005;
	u -= r * sin(theta * M_PI / 180.0f);
	v -= r * cos(theta * M_PI / 180.0f);
}

void Hero_tim::moveToCurrentPoint() {
	Point current_point = getCurrentPoint();
	getTransform().setPosition(Vector3(current_point.getX(), current_point.getY(), current_point.getZ()));
	//
	// Vector3 tangent = getCurrentTangent();
	// float rotation_angle = 180.0f / M_PI * acos(tangent.dot(Vector3::forward()));
	// Vector3 rotation_axis = Vector3::forward().cross(tangent);
	// getTransform().setRotation(rotation_axis, rotation_angle);
}

float Hero_tim::getU() {
	return u;
}

float Hero_tim::getV() {
	return v;
}

Point Hero_tim::getCurrentPoint() {
	Point point = getPatch().getPointFromUV(getU(), getV());
	return point;
}

Vector3 Hero_tim::getCurrentTangent() {
	Vector3 tangent = getPatch().getTangentFromUV(getU(), getV());
	return tangent;
}

void Hero_tim::ensureInBounds() {
    u = fmax(getU(), 0);
    u = fmin(getU(), 1);
    v = fmax(getV(), 0);
    v = fmin(getV(), 1);
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

BezierPatch& Hero_tim::getPatch() {
	return *patch;
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

void Hero_tim::turnLeft() {
	theta = theta + 2;
	computeDirection();
}

void Hero_tim::turnRight() {
	theta = theta - 2;
	computeDirection();
}

void Hero_tim::computeDirection() {
	dirX = sin(theta * M_PI / 180.0f);
	dirZ = cos(theta * M_PI / 180.0f);
	getTransform().setRotation(Vector3(0, 1, 0), theta);
}
