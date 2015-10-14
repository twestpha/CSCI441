#ifndef ArcballCamera_h
#define ArcballCamera_h

#include <stdio.h>
#include <algorithm>
#include "math_safe.hpp"
#include "gl_includes.hpp"

#include "Drawable.hpp"
#include "Camera.hpp"

class ArcBallCamera : public Camera {
public:
    // Constructors
  ArcBallCamera();
  ArcBallCamera(float theta, float phi);
  ArcBallCamera(float x, float y, float z);
  ArcBallCamera(float x, float y, float z, float theta, float phi);
  ArcBallCamera(float x, float y, float z, float theta, float phi, float radius);

  // Methods (Inherited)
  void update();

  // Getters (Inherited)
  float getLookAtX(){ return 0.0; }
  float getLookAtY(){ return 0.0; }
  float getLookAtZ(){ return 0.0; }

  float getRadius(){ return radius; }

  // Setters (Inherited)
  void setRadius(float newRadius){ radius = std::max(0.1f, newRadius); }

  // Incrementers (Inherited)
  void incrementRadius(float amount){
       radius+=(sensitivity*amount);
       radius = std::max(0.1f, radius);
   }

    void handleKeyboard(Keyboard& keyboard);

private:
  float radius;
};

#endif
