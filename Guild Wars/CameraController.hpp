#ifndef CameraController_h
#define CameraController_h

#include <stdio.h>
#include <algorithm>
#include "math_safe.hpp"
#include "gl_includes.hpp"

#include "Drawable.hpp"
#include "Camera.hpp"

class CameraController {
public:
  // Constructors
  CameraController(Camera* camera);
  Camera& getCurrentCamera();
  Drawable& getParent();

  // Methods
  void update();

  // Inputs
  void handleInput(float xInput, float yInput, float zInput);

  // Setters
  void setParent(Drawable* object){ parent = object; }

private:
  Camera* currentCamera;
  Drawable* parent;
};

#endif
