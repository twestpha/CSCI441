// Camera.h
// Trevor Westphal
//
// Definitions for Camera controller, abstract Camera object,
// And subclasses for the Arcball and FreeCam child objects.

#ifndef Camera_h
#define Camera_h

#include <stdio.h>
#include <algorithm>
#include "math_safe.hpp"
#include "gl_includes.hpp"

#include "Drawable.hpp"
#include "Keyboard.hpp"

class Camera {
public:
  // Constructors
  Camera();
  Camera(float theta, float phi);
  Camera(float x, float y, float z);
  Camera(float x, float y, float z, float theta, float phi);

  // Methods
  virtual void update() = 0;

  // Getters
  float getX(){ return x; }
  float getY(){ return y; }
  float getZ(){ return z; }

  virtual float getLookAtX() = 0;
  virtual float getLookAtY() = 0;
  virtual float getLookAtZ() = 0;

  float getTheta(){ return theta; }
  float getPhi(){ return phi; }

  virtual float getRadius() = 0;

  // Setters
  void setX(float newX){ x = newX; }
  void setY(float newY){ y = newY; }
  void setZ(float newZ){ z = newZ; }

  void setTheta(float newTheta){ theta = newTheta; }
  void setPhi(float newPhi){ phi = std::min(std::max(newPhi, 1.0f), 179.0f); }

  void setSensitivity(float newSensitivity){ sensitivity = newSensitivity; }

  virtual void setRadius(float newRadius) = 0;

  virtual void handleKeyboard(Keyboard& keyboard) = 0;

  // Incrementers
  void incrementTheta(float amount){ theta+=(amount*sensitivity); }
  void incrementPhi(float amount){
      phi+=(amount*sensitivity);
      phi = std::min(std::max(phi, 1.0f), 179.0f);
  }

  virtual void incrementRadius(float amount) = 0;

protected:
  float x, y, z;    // Location in cartesian coords
  float theta, phi; // Orientation in spherical coords
  float sensitivity;// Sensitivity of incrementing operations
};

#endif
