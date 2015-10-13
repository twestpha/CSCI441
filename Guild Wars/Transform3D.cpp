#include "Transform3D.hpp"

Transform3D::Transform3D() {
    setScale(Vector3(1, 1, 1));
    setPosition(Vector3(0, 0, 0));
    setRotation(Vector3(0, 0, 1), 0);
}

Transform3D::Transform3D(Vector3 position) {
    setScale(Vector3(1, 1, 1));
    setPosition(position);
    setRotation(Vector3(0, 0, 1), 0);
}

Transform3D::Transform3D(Vector3 position, Vector3 scale) {
    setScale(scale);
    setPosition(position);
    setRotation(Vector3(0, 0, 1), 0);
}

void Transform3D::apply() {
    glTranslatef(getPosition().x, getPosition().y, getPosition().z);
    glRotatef(
        getRotationAngle(),
        getRotationAxis().x,
        getRotationAxis().y,
        getRotationAxis().z);
    glScalef(getScale().x, getScale().y, getScale().z);
}

void Transform3D::moveBy(Vector3 move_vector) {
    setPosition(Vector3(getPosition() + move_vector));
}

void Transform3D::setScale(Vector3 scale) {
    this->scale = scale;
}

void Transform3D::setPosition(Vector3 position) {
    this->position = position;
}


Vector3 Transform3D::getScale() {
    return scale;
}

Vector3 Transform3D::getPosition() {
    return position;
}

void Transform3D::setRotation(Vector3 rotation_axis, float rotation_angle) {
    setRotationAxis(rotation_axis);
    setRotationAngle(rotation_angle);
}

Vector3 Transform3D::getRotationAxis() {
    return rotation_axis;
}
float Transform3D::getRotationAngle() {
    return rotation_angle;
}

void Transform3D::setRotationAxis(Vector3 rotation_axis) {
    this->rotation_axis = rotation_axis;
}
void Transform3D::setRotationAngle(float angle) {
    this->rotation_angle = angle;
}
