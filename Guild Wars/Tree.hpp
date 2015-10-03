#ifndef tree_h
#define tree_h

#include "Drawable.hpp"
#include "Tree.hpp"
#include "gl_includes.hpp"

class Tree : public Drawable {
public:
	Tree(float x, float y, float z);
	void draw();
};

#endif
