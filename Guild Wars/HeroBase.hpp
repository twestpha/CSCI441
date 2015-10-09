#pragma once
#include <string>

#include <memory>

using namespace std;

class HeroBase {
public: 
	HeroBase(Transform3D transform) : transform(move(transform)) { ; }
	virtual void draw() = 0;
	virtual void updateAnimation() = 0;
private:
	Transform3D transform;
};

