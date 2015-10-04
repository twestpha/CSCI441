// Camera.cpp
// Trevor Westphal
//
// Implementation for Camera controller, abstract Camera object,
// And subclasses for the Arcball and FreeCam child objects.
#include "Camera.hpp"

//######################################################################
// Camera base object
//######################################################################
Camera::Camera(){
   x = 0.0;
   y = 0.0;
   z = 0.0;
   theta = 0.0;
   phi = 0.0;
   sensitivity = 1.0;
}

Camera::Camera(float theta, float phi){
  x = 0.0;
  y = 0.0;
  z = 0.0;
  this->theta = theta;
  this->phi = phi;
  sensitivity = 1.0;
}

Camera::Camera(float x, float y, float z){
  this->x = x;
  this->y = y;
  this->z = z;
  theta = 0.0;
  phi = 0.0;
  sensitivity = 1.0;
}

Camera::Camera(float x, float y, float z, float theta, float phi){
  this->x = x;
  this->y = y;
  this->z = z;
  this->theta = theta;
  this->phi = phi;
  sensitivity = 1.0;
}

//######################################################################
// Camera Controller object
//######################################################################
CameraController::CameraController(){
  // Create default camera (Arcball)
  currentCamera = new ArcBallCamera();

	// Free cam is very sensitive
  // getCurrentCamera().setSensitivity(0.01);

  getCurrentCamera().setTheta(-90.0);
  getCurrentCamera().setPhi(45.0);
}

Camera& CameraController::getCurrentCamera(){
	return *currentCamera;
}

Drawable& CameraController::getParent(){
	return *parent;
}

void CameraController::update(){
  getCurrentCamera().update();

  if(parent){
	  gluLookAt(  getCurrentCamera().getX() + getParent().getX(),
	  			  getCurrentCamera().getY() + getParent().getY(),
	   			  getCurrentCamera().getZ() + getParent().getZ(),
	              getCurrentCamera().getLookAtX() + getParent().getX(),
				  getCurrentCamera().getLookAtY() + getParent().getY(),
				  getCurrentCamera().getLookAtZ() + getParent().getZ(),
	              0,  1,  0);
	} else {
		gluLookAt(  getCurrentCamera().getX(),
  	  			  getCurrentCamera().getY(),
  	   			  getCurrentCamera().getZ(),
  	              getCurrentCamera().getLookAtX(),
  				  getCurrentCamera().getLookAtY(),
  				  getCurrentCamera().getLookAtZ(),
  	              0,  1,  0);
	}
}

void CameraController::handleInput(float xInput, float yInput, float zInput){
	getCurrentCamera().incrementTheta(xInput);
	getCurrentCamera().incrementPhi(-1 * yInput);
	getCurrentCamera().incrementRadius(zInput);
}

//######################################################################
// Arc Ball Camera object
//######################################################################
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

//######################################################################
// Free Camera object
//######################################################################
FreeCamera::FreeCamera(){
	// Stubby for now! Hooray!
}

void FreeCamera::update(){
	// Calculate the direction vector of the lookat
	float directionVectorX = sin(theta) * sin(phi);
    float directionVectorY = -1 * cos(phi);
    float directionVectorZ = -1 * cos(theta) * sin(phi);
    float magnitude = sqrt((directionVectorX * directionVectorX) + (directionVectorY * directionVectorY) + (directionVectorZ * directionVectorZ));

    // and NORMALIZE the directional vector
    lookAtX = directionVectorX / magnitude;
    lookAtY = directionVectorY / magnitude;
    lookAtZ = directionVectorZ / magnitude;
}
