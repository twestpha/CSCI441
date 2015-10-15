#ifndef hero_base_h
#define hero_base_h

#include <string>
#include <memory>

#include "Transform3D.hpp"

using namespace std;

class HeroBase {
public:
	HeroBase(string name) : name(name)  { ; }
	HeroBase(Transform3D transform, string name) : transform(move(transform)), name(name) { ; }
	virtual void draw() = 0;
	virtual void updateAnimation() = 0;

	Transform3D& getTransform() { return transform; }
	void setTransform(Transform3D t){ transform = t; }
	string getName() {return name;}
private:
	Transform3D transform;
	string name;
};
#endif
