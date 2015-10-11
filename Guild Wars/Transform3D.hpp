// Transform3D
//      A Transform3D abstracts the OpenGL transformations for me so that I can just tell something to be at a certain position, rotation, or have a cetain scale. Also you can tell it a vector to move by and an angle to rotate by. apply() just calls the necessary OpenGL functions to preform the transformation.
#ifndef Transform3D_h
#define Transform3D_h

#include "gl_includes.hpp"

#include "Vector3.hpp"

class Transform3D {
public:

    Transform3D();
    Transform3D(Vector3 position);
    Transform3D(Vector3 position, Vector3 scale);

    void apply();

    void setScale(Vector3 scale);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation_axis, float rotation_angle);

    Vector3 getScale();
    Vector3 getPosition();
    Vector3 getRotationAxis();
    float getRotationAngle();

    void moveBy(Vector3 move_vector);


private:
    void setRotationAxis(Vector3 rotation_axis);
    void setRotationAngle(float angle);

    Vector3 scale;
    Vector3 position;
    Vector3 rotation_axis;
    float rotation_angle;

};

#endif
