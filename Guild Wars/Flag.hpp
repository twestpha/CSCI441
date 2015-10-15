#ifndef flag_h
#define flag_h

#include "Drawable.hpp"
#include "gl_includes.hpp"
#include "Material.hpp"

class Flag : public Drawable {
public:
	Flag(float x, float y, float z);
	void draw();
};

#endif
