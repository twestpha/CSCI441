#include "Drawable.hpp"

#ifndef tree_h
#define tree_h

class Tree : public Drawable {
public:
	Tree(float x, float y, float z);
	void draw();
};

#endif