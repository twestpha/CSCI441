#include "drawable.h"

#ifndef fuselage_h
#define fuselage_h

class Fuselage : public Drawable {
public:
	Fuselage(float x, float y, float z);
	void draw();
};

#endif