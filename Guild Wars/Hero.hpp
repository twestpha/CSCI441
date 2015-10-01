#include "Drawable.hpp"

#ifndef hero_h
#define hero_h

class Hero : public Drawable {
public:
	Hero(float x, float y, float z);
	void draw();
};

#endif