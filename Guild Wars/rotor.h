#include "drawable.h"

#ifndef rotor_h
#define rotor_h

class Rotor : public Drawable {
public:
	Rotor(float x, float y, float z);
	void draw();
private:
	int rotation;
};

#endif