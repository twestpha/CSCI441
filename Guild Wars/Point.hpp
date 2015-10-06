#ifndef point_h
#define point_h

#include "Vector3.hpp"
#include "gl_includes.hpp"

class Point {
public:
	Point();
	Point(float x, float y, float z);

	// Getters and Setters
	float getX(){ return x;}
	float getY(){ return y;}
	float getZ(){ return z;}

	void draw();
	static void drawLineBetween(Point& p0, Point& p1, float thickness, Vector3 color);

private:
	float x, y, z;
};

// Operator overloads
Point operator*(Point p, float f);
Point operator*(float f, Point p);
Point operator+(Point a, Point b);
Point operator-(Point a, Point b);

#endif
