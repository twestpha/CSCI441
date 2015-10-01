#include "drawable.h"

#ifndef wings_h
#define wings_h

class Wings : public Drawable {
public:
	Wings(float x, float y, float z);
	void draw();
private:
	int rotation;
};

#endif
