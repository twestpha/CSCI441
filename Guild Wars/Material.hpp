#ifndef Material_h
#define Material_h

#include "gl_includes.hpp"
#include "Color.hpp"

class Material {
public:
    Material(Color diffuse, Color specular, Color ambient);

    void apply();

private:
    Color diffuse;
    Color specular;
    Color ambient;
};

#endif
