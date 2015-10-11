#ifndef CameraController_h
#define CameraController_h

#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "math_safe.hpp"
#include "gl_includes.hpp"


#include "Drawable.hpp"
#include "Camera.hpp"

using namespace std;

class CameraController {
public:
  // Constructors
  CameraController(Camera& camera, float sensitivity);
  Camera& getCurrentCamera();
  Drawable& getParent();

  // Methods
  void update();

  // Inputs
  void handleInput(float xInput, float yInput, float zInput);

  // Setters
  void setParent(Drawable* object){ parent = object; }
  void setSensitivity(float sensitivity);
  void setCurrentCamera(Camera& camera);

  // Getters
  float getSensitivity();

private:
  Camera* currentCamera;
  float sensitivity;
  Drawable* parent;
};

#endif
