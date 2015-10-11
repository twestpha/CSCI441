#ifndef FreeCamera_h
#define FreeCamera_h

#include <stdio.h>
#include <algorithm>
#include "math_safe.hpp"
#include "gl_includes.hpp"

#include "Drawable.hpp"
#include "Camera.hpp"

class FreeCamera : public Camera {
public:
  FreeCamera();

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
  float lookAtX;
  float lookAtY;
  float lookAtZ;
};

#endif
