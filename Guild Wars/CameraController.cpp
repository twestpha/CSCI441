#include "CameraController.hpp"

CameraController::CameraController(Camera& camera, float sensitivity) : currentCamera(&camera), sensitivity(sensitivity) {

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
	getCurrentCamera().incrementTheta(getSensitivity() * xInput);
	getCurrentCamera().incrementPhi(-1 * getSensitivity() * yInput);
	getCurrentCamera().incrementRadius(zInput);
}

void CameraController::setCurrentCamera(Camera& camera) {
	cout << "Gonna use a new camera!\n";
	cout << "&camera = " << &camera << "\n";
	this->currentCamera = &camera;
	cout << "&currentCamera = " << &(getCurrentCamera()) << "\n";
}

void CameraController::setSensitivity(float sensitivity) {
	this->sensitivity = sensitivity;
}

float CameraController::getSensitivity() {
	return sensitivity;
}
