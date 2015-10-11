#ifndef FreeCamera_h
#define FreeCamera_h

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
