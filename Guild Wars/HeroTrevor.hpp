#ifndef HeroTrevor_h
#define HeroTrevor_h

#include "gl_includes.hpp"

#include "HeroBase.hpp"
#include "Material.hpp"

class HeroTrevor : public HeroBase {
public:
    HeroTrevor(Transform3D transform, string name);

    void draw();
    void updateAnimation();

    void walk();
    void stopWalking();

private:
    void drawHero();
};

#endif
