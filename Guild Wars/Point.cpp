#include "Point.hpp"

#include "Vector3.hpp"

Point::Point(){
	// Empty constructor
}

Point::Point(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Point operator*(Point p, float f){
	return Point(f * p.getX(), f * p.getY(), f * p.getZ());
}

Point operator*(float f, Point p){
	return p * f;
}

Point operator+(Point a, Point b){
	return Point(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Point operator-(Point a, Point b){
	return Point(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}
