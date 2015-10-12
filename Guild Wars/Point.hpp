#ifndef point_h
#define point_h

class Point {
public:
	Point();
	Point(float x, float y, float z);

	// Getters and Setters
	float getX(){ return x;}
	float getY(){ return y;}
	float getZ(){ return z;}

private:
	float x, y, z;
};

// Operator overloads
Point operator*(Point p, float f);
Point operator*(float f, Point p);
Point operator+(Point a, Point b);
Point operator-(Point a, Point b);

#endif
