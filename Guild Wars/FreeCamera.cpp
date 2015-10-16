#include "FreeCamera.hpp"

FreeCamera::FreeCamera(Transform3D& parent) : Camera(), parent(&parent) {
	// Stubby for now! Hooray!
	incrementPhi(M_PI / 2.0f);
	incrementTheta(0);
	incrementRadius(0);
}

FreeCamera::FreeCamera(float x, float y, float z) : Camera(x, y, z) {
	incrementPhi(M_PI / 2.0f);
	incrementTheta(0);
	incrementRadius(0);
}


FreeCamera::FreeCamera(float x, float y, float z, float theta, float phi) : Camera(x, y, z, theta, phi) {

}

void FreeCamera::update(){

	if (hasParent()) {
		height_offset = height_offset ? height_offset : 6.5;
		x = getParent().getPosition().x;
		y = getParent().getPosition().y + height_offset;
		z = getParent().getPosition().z;

		Vector3 rotation_axis = getParent().getRotationAxis().unit();
		float rotation_angle = getParent().getRotationAngle() * M_PI / 180.0f;

		float x = rotation_axis.x;
		float y = rotation_axis.y;
		float z = rotation_axis.z;
		float angle = rotation_angle;

		float y_angle = atan2(y * sin(angle)- x * z * (1 - cos(angle)) , 1 - (y*y + z*z ) * (1 - cos(angle)));
		setTheta(M_PI - y_angle);

	}

	// Calculate the direction vector of the lookat
	directionVectorX = sin(theta) * sin(phi);
    directionVectorY = -1 * cos(phi);
    directionVectorZ = -1 * cos(theta) * sin(phi);
    float magnitude = sqrt((directionVectorX * directionVectorX) + (directionVectorY * directionVectorY) + (directionVectorZ * directionVectorZ));

    // and NORMALIZE the directional vector
    lookAtX = directionVectorX / magnitude + getX();
    lookAtY = directionVectorY / magnitude + getY();
    lookAtZ = directionVectorZ / magnitude + getZ();
}

void FreeCamera::handleKeyboard(Keyboard& keyboard) {
	if (keyboard.isKeyDown('w')) {
		x += directionVectorX;
		y += directionVectorY;
		z += directionVectorZ;
	}
	if (keyboard.isKeyDown('s')) {
		x -= directionVectorX;
		y -= directionVectorY;
		z -= directionVectorZ;
	}
}

bool FreeCamera::hasParent() {
	return parent != NULL;
}

Transform3D& FreeCamera::getParent() {
	return *parent;
}

void FreeCamera::setParent(Transform3D& parent, float height_offset) {
	this->parent = &parent;
	this->height_offset = height_offset;
}
