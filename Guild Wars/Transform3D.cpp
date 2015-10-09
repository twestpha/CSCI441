#include "Transform3D.hpp"

Transform3D::Transform3D() {
    setScale(Vector3(1, 1, 1));
    setPosition(Vector3(0, 0, 0));
    setRotation(0);
}

Transform3D::Transform3D(Vector3 position) {
    setScale(Vector3(1, 1, 1));
    setPosition(position);
    setRotation(0);
}

Transform3D::Transform3D(Vector3 position, Vector3 scale) {
    setScale(scale);
    setPosition(position);
    setRotation(0);
}

void Transform3D::apply() {
    glTranslatef(getPosition().x, getPosition().y, getPosition().z);
    glRotatef(getRotation(), 0, 0, 1);
    glScalef(getScale().x, getScale().y, 0);
}

void Transform3D::moveBy(Vector3 move_vector) {
    setPosition(Vector3(getPosition() + move_vector));
}

void Transform3D::rotateBy(float angle) {
    setRotation(getRotation() + angle);
}

void Transform3D::setScale(Vector3 scale) {
    this->scale = scale;
}

void Transform3D::setPosition(Vector3 position) {
    this->position = position;
}

void Transform3D::setRotation(float rotation) {
    this->rotation = rotation;
}

Vector3 Transform3D::getScale() {
    return scale;
}

Vector3 Transform3D::getPosition() {
    return position;
}

float Transform3D::getRotation() {
    return rotation;
}
