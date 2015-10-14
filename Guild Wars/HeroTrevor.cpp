#include "HeroTrevor.hpp"

HeroTrevor::HeroTrevor(Transform3D transform, string name) : HeroBase(transform, name) {
}

void HeroTrevor::updateAnimation(){
    
}


void HeroTrevor::draw() {
    glPushMatrix();
        getTransform().apply();
        drawHero();
    glPopMatrix();
}

void HeroTrevor::drawHero() {
    glutSolidCube(1);
}