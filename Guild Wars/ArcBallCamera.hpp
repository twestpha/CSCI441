#ifndef ArcballCamera_h
#define ArcballCamera_h

#include <stdio.h>
#include <algorithm>
#include "math_safe.hpp"
#include "gl_includes.hpp"

#include "Drawable.hpp"
#include "Camera.hpp"
#include "Transform3D.hpp"

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
  float getLookAtX();
  float getLookAtY();
  float getLookAtZ();

  float getRadius(){ return radius; }

  // Setters (Inherited)
  void setRadius(float newRadius){ radius = std::max(0.1f, newRadius); }

  // Incrementers (Inherited)
  void incrementRadius(float amount){
       radius+=(sensitivity*amount);
       radius = std::max(0.1f, radius);
   }

    void handleKeyboard(Keyboard& keyboard);

	void setParent(Transform3D& parent);

private:
  float radius;
  Transform3D* parent;
  bool hasParent();
  Transform3D& getParent();
};

#endif
