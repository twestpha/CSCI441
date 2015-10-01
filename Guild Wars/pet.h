#ifndef pet_h
#define pet_h

#include "drawable.h"
#include "beziercurve.h"
#include "wings.h"

class Pet : public Drawable {
public:
    Pet(float x, float y, float z);
    void draw(BezierCurve &b);
private:
    float t;
    Wings w;
};

#endif
