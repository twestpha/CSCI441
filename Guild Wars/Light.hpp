#ifndef Light_h
#define Light_h

#include <memory>

#include "Transform3D.hpp"
#include "Color.hpp"

using namespace std;

class Light {
public:
    Light();
    Light(Transform3D transform_3D, Color diffuse, Color ambient);

    void tellOpenGL();

    Transform3D& getTransform3D();
    Color getDiffuseColor();
    Color getAmbientColor();

    static GLuint global_light_number;

    void enable();
    GLuint getLightNumber();


private:
    Transform3D transform_3D;
    Color diffuse;
    Color ambient;
    GLuint light_number;

    void setGLLightColors();
    void setGLLightPosition();

    void figureOutLightNumber();

};

#endif
