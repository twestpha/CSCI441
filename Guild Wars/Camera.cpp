// Camera.cpp
// Trevor Westphal
//
// Implementation for Camera controller, abstract Camera object,
// And subclasses for the Arcball and FreeCam child objects.
#include "Camera.hpp"

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
