#ifndef drawable_h
#define drawable_h

class Drawable {
public:
	Drawable(float x, float y, float z, float rotX, float rotY, float rotZ);
	Drawable(float x, float y, float z);
	void setColor(float r, float g, float b);
	virtual void draw(){}
	float getX(){return x;}
	float getY(){return y;}
	float getZ(){return z;}
protected:
	float x, y, z;
	float rotX, rotY, rotZ;
	float r, g, b;
};

#endif