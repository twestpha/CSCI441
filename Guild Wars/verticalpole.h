#include "drawable.h"

#ifndef vertical_pole_h
#define vertical_pole_h

class VerticalPole : public Drawable {
public:
	VerticalPole(float x, float y, float z);
	void draw();
};

#endif