#include "Drawable.hpp"

#ifndef horizontal_pole_h
#define horizontal_pole_h

class HorizontalPole : public Drawable {
public:
	HorizontalPole(float x, float y, float z);
	void draw();
};

#endif