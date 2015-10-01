// Camera.h
// Trevor Westphal
//
// Definitions for Camera controller, abstract Camera object,
// And subclasses for the Arcball and FreeCam child objects.

#include <algorithm>

#include "Drawable.hpp"

#ifndef camera_h
#define camera_h

//######################################################################
// Camera base object
//######################################################################
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

//######################################################################
// Camera Controller object
//######################################################################
class CameraController {
public:
  // Constructors
  CameraController();
  Camera& getCurrentCamera();
  Drawable& getParent();

  // Methods
  void update();

  // Inputs
  void handleInput(float xInput, float yInput, float zInput);

  // Setters
  void setParent(Drawable* object){ parent = object; }

private:
  Camera *currentCamera;
  Drawable *parent;
};

//######################################################################
// Arc Ball Camera object
//######################################################################
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

private:
  float radius;
};

//######################################################################
// Free Camera object
//######################################################################
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
