#ifndef HeroChris_h
#define HeroChris_h

#include "gl_includes.hpp"

#include "HeroBase.hpp"
#include "Material.hpp"

class HeroChris : public HeroBase {
public:
    HeroChris(Transform3D transform, string name);

    void draw();
    void updateAnimation();

    void walk();
    void stopWalking();
    
private:
    float body_scale;
    float leg_rotation;
    float time;
    bool is_walking;

    void drawLeg();
    void drawBody();
    void drawArm();
    void drawHead();
    void drawHero();
};

#endif
