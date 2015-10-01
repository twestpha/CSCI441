#include "drawable.h"

#ifndef propeller_h
#define propeller_h

class Propeller : public Drawable {
public:
	Propeller(float x, float y, float z);
	void draw();
	void moving();
private:
	int rotation;
};

#endif