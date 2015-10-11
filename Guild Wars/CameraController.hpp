#ifndef CameraController_h
#define CameraController_h

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

#endif
