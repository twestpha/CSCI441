#include "HeroTrevor.hpp"

HeroTrevor::HeroTrevor(Transform3D transform, string name) : HeroBase(transform, name) {
    theta = 0.0;
}

void HeroTrevor::updateAnimation(){
    theta += 0.1;
}


void HeroTrevor::draw() {
    glPushMatrix();
        getTransform().apply();
        glTranslatef(0, 1.5, 0);
        drawHero();
    glPopMatrix();
}

void HeroTrevor::drawHero() {
    drawHead();
    drawBody();

    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.0);
        drawArm();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.0, 0.0, 0.0);
        drawArm();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5, 0.0, 0.0);
        drawLeftLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5, 0.0, 0.0);
        drawRightLeg();
    glPopMatrix();
}

void HeroTrevor::drawHead(){
    Material head_material(Color(0.98, 0.93, 0.7), Color(), Color());
    head_material.apply();
    glPushMatrix();
        glTranslatef(0.0, 4.0, 0.0);
        glutSolidCube(1);
    glPopMatrix();
}

void HeroTrevor::drawBody(){
    Material body_material(Color(0.5, 0.5, 0.0), Color(), Color());
    body_material.apply();
    glPushMatrix();
        glTranslatef(0.0, 2.5, 0.0);
        glScalef(1.0, 2.0, 1.0);
        glutSolidCube(1);
    glPopMatrix();
}

void HeroTrevor::drawArm(){
    Material arm_material(Color(0.98, 0.93, 0.7), Color(), Color());
    arm_material.apply();
    glPushMatrix();
        glTranslatef(0.0, 2.5, 0.0);
        glScalef(0.5, 2.0, 0.5);
        glutSolidCube(1);
    glPopMatrix();
}

void HeroTrevor::drawLeftLeg(){
    Material leg_material(Color(0.5, 0.5, 0.0), Color(), Color());
    leg_material.apply();
    glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glRotatef(sin(theta) * 30.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -1.0, 0.0);

        glScalef(0.5, 2.0, 0.5);
        glutSolidCube(1);
    glPopMatrix();
}

void HeroTrevor::drawRightLeg(){
    Material leg_material(Color(0.5, 0.5, 0.0), Color(), Color());
    leg_material.apply();
    glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glRotatef(sin(theta) * -30.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -1.0, 0.0);

        glScalef(0.5, 2.0, 0.5);
        glutSolidCube(1);
    glPopMatrix();
}
