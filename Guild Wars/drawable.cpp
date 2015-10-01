#include "Drawable.hpp"

Drawable::Drawable(float x, float y, float z, float rotX, float rotY, float rotZ){
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	r = 1.0;
	g = 0.0;
	b = 1.0;
}

Drawable::Drawable(float x, float y, float z) : Drawable(x, y, z, 0.0, 0.0, 0.0){
}

void Drawable::setColor(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
}