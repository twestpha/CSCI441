#include "ArcballCamera.hpp"

ArcBallCamera::ArcBallCamera() : Camera() {
  radius = 10.0;
}

ArcBallCamera::ArcBallCamera(float theta, float phi) : Camera(theta, phi) {
  radius = 10.0;
}

ArcBallCamera::ArcBallCamera(float x, float y, float z) : Camera(x, y, z){
  radius = 10.0;
}

ArcBallCamera::ArcBallCamera(float x, float y, float z, float theta, float phi) : Camera(x, y, z, theta, phi){
	radius = 10.0;
}

ArcBallCamera::ArcBallCamera(float x, float y, float z, float theta, float phi, float radius) : Camera(x, y, z, theta, phi){
  this->radius = radius;
}

void ArcBallCamera::handleKeyboard(Keyboard& keyboard) {

}


void ArcBallCamera::update(){
	float cameraThetaRad = theta * M_PI / 180.0;
	float cameraPhiRad = phi * M_PI / 180.0;

	x = radius * sin(cameraPhiRad) * cos(cameraThetaRad);
	y = radius * cos(cameraPhiRad);
	z = radius * sin(cameraPhiRad) * sin(cameraThetaRad);

    if (hasParent()) {
        x += getParent().getPosition().x;
        y += getParent().getPosition().y;
        z += getParent().getPosition().z;
    }
}

Transform3D& ArcBallCamera::getParent() {
	return *parent;
}

void ArcBallCamera::setParent(Transform3D& parent) {
	this->parent = &parent;
}

bool ArcBallCamera::hasParent() {
    return parent != NULL;
}

float ArcBallCamera::getLookAtX() {
	if (parent != NULL) {
		return getParent().getPosition().x;
	}
	else {
		return 0.0;
	}
}

float ArcBallCamera::getLookAtY() {
	if (parent != NULL) {
		return getParent().getPosition().y;
	}
	else {
		return 0.0;
	}
}

float ArcBallCamera::getLookAtZ() {
	if (parent != NULL) {
		return getParent().getPosition().z;
	}
	else {
		return 0.0;
	}
}
