#ifndef FreeCamera_h
#define FreeCamera_h

#include <stdio.h>
#include <algorithm>
#include "math_safe.hpp"
#include "gl_includes.hpp"

#include "Drawable.hpp"
#include "Camera.hpp"
#include "Transform3D.hpp"

class FreeCamera : public Camera {
public:
    FreeCamera(Transform3D& parent);
    FreeCamera(float x, float y, float z);

    void update();

    // Getters (Inherited)
    float getLookAtX(){ return lookAtX; }
    float getLookAtY(){ return lookAtY; }
    float getLookAtZ(){ return lookAtZ; }

    float getRadius(){ return 0.0; }

    // Setters (Inherited)
    void setRadius(float newRadius){}

    // Incrementers (Inherited)
    void incrementRadius(float amount){}


private:
    Transform3D* parent;
    float lookAtX;
    float lookAtY;
    float lookAtZ;

    bool hasParent();
    Transform3D& getParent();
};

#endif
