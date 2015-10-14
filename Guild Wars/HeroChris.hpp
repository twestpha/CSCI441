#ifndef HeroChris_h
#define HeroChris_h

#include "gl_includes.hpp"

#include "HeroBase.hpp"

class HeroChris : public HeroBase {
public:
    HeroChris(Transform3D transform, string name) : HeroBase(transform, name) {;}

    void draw();
    void updateAnimation();
private:

};

#endif
