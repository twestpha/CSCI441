#include "FreeCamera.hpp"

FreeCamera::FreeCamera(Transform3D& parent) : Camera(), parent(&parent) {
	// Stubby for now! Hooray!
	incrementPhi(30);
	incrementTheta(0);
	incrementRadius(0);
}

FreeCamera::FreeCamera(float x, float y, float z) : Camera(x, y, z) {
	incrementPhi(30);
	incrementTheta(0);
	incrementRadius(0);
}

void FreeCamera::update(){
	if (hasParent()) {
		float height_offset = 6.5;
		x = getParent().getPosition().x;
		y = getParent().getPosition().y + height_offset;
		z = getParent().getPosition().z;
	}

	// Calculate the direction vector of the lookat
	float directionVectorX = sin(theta) * sin(phi);
    float directionVectorY = -1 * cos(phi);
    float directionVectorZ = -1 * cos(theta) * sin(phi);
    float magnitude = sqrt((directionVectorX * directionVectorX) + (directionVectorY * directionVectorY) + (directionVectorZ * directionVectorZ));

    // and NORMALIZE the directional vector
    lookAtX = directionVectorX / magnitude + getX();
    lookAtY = directionVectorY / magnitude + getY();
    lookAtZ = directionVectorZ / magnitude + getZ();
}

bool FreeCamera::hasParent() {
	return parent != NULL;
}

Transform3D& FreeCamera::getParent() {
	return *parent;
}
