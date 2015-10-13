#ifndef hero_base_h
#define hero_base_h

#include <string>
#include <memory>

#include "Transform3D.hpp"

using namespace std;

class HeroBase {
public: 
	HeroBase(Transform3D transform) : transform(move(transform)) { ; }
	virtual void draw() = 0;
	virtual void updateAnimation() = 0;

	Transform3D& getTransform() { return transform; }
private:
	Transform3D transform;
};
#endif
