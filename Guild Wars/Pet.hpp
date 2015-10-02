#ifndef pet_h
#define pet_h

#include "Drawable.hpp"
#include "BezierCurve.hpp"
#include "Wings.hpp"
#include "Pet.hpp"
#include "Drawable.hpp"
#include "BezierCurve.hpp"
#include "Point.hpp"

#include "gl_includes.hpp"


class Pet : public Drawable {
public:
    Pet(float x, float y, float z);
    void draw(BezierCurve &b);
private:
    float t;
    Wings w;
};

#endif
