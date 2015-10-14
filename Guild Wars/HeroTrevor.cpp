#include "HeroTrevor.hpp"

HeroTrevor::HeroTrevor(Transform3D transform, string name) : HeroBase(transform, name) {

    body_scale = 1;
    leg_rotation = 0;
}


void HeroTrevor::draw() {
    glPushMatrix();
        glTranslatef(0, 4, 0);
        getTransform().apply();
        drawHero();
    glPopMatrix();
}

void HeroTrevor::updateAnimation() {
    time += 1;

    if (is_walking) {
        leg_rotation = 30 * sin(time * 0.1);
        body_scale = 1;
    } else {
        leg_rotation = 0;
        body_scale = 0.01 * sin(time * 0.01) + 1;
    }
}

void HeroTrevor::walk() {
    leg_rotation = 0;
    body_scale = 1;
    is_walking = true;
}

void HeroTrevor::stopWalking() {
    leg_rotation = 0;
    body_scale = 1;
    is_walking = false;
}

void HeroTrevor::drawHero() {
    glPushMatrix();
        glScalef(body_scale, body_scale, body_scale);
        drawBody();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1, 0.75, 0);
        drawArm();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1, 0.75, 0);
        drawArm();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 1.5, 0);
        drawHead();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.55, 0, 0);
        glRotatef(leg_rotation, 1, 0, 0);
        glTranslatef(0, -2.5, 0);
        drawLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.55, 0, 0);
        glRotatef(-leg_rotation, 1, 0, 0);
        glTranslatef(0, -2.5, 0);
        drawLeg();
    glPopMatrix();
}

void HeroTrevor::drawArm() {
    Material arm_material(Color(0.98, 0.93, 0.7), Color(), Color());
    arm_material.apply();
    glScalef(3, 1, 0.7);
    glutSolidCube(1);
}

void HeroTrevor::drawBody() {
    Material body_material(Color(0.55, 0.16, 0.16), Color(), Color());
    body_material.apply();
    glScalef(2, 3, 1);
    glutSolidCube(1);
}

void HeroTrevor::drawHead() {
    Material head_material(Color(0.98, 0.93, 0.7), Color(), Color());
    head_material.apply();
    glScalef(1.25, 1.25, 1.25);
    glutSolidCube(1);
}

void HeroTrevor::drawLeg() {
    Material leg_material(Color(0.31, 0.28, 0.17), Color(), Color());
    leg_material.apply();
    glPushMatrix();
        glScalef(1, 3, 1);
        glutSolidCube(1);
    glPopMatrix();
}
