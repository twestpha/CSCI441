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

void ArcBallCamera::update(){
	float cameraThetaRad = theta * M_PI / 180.0;
	float cameraPhiRad = phi * M_PI / 180.0;

	x = radius * sin(cameraPhiRad) * cos(cameraThetaRad);
	y = radius * cos(cameraPhiRad);
	z = radius * sin(cameraPhiRad) * sin(cameraThetaRad);
}
