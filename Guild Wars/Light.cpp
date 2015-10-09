#include "Light.hpp"

GLuint Light::global_light_number = GL_LIGHT0;  // Why I have to init it here?

Light::Light(Transform3D transform_3D, Color diffuse, Color ambient) : transform_3D(move(transform_3D)), diffuse(diffuse), ambient(ambient) {

    figureOutLightNumber();

}

void Light::tellOpenGL() {
    enable();
    setGLLightColors();
    setGLLightPosition();
}

void Light::setGLLightColors() {
    float diffuseCol[4] = {
        getDiffuseColor().r,
        getDiffuseColor().g,
        getDiffuseColor().b,
        1.0
    };
    glLightfv( getLightNumber(), GL_DIFFUSE, diffuseCol );

    float ambientCol[4] = {
        getAmbientColor().r,
        getAmbientColor().g,
        getAmbientColor().b,
        1.0
    };
    glLightfv( getLightNumber(), GL_AMBIENT, ambientCol );
}

void Light::setGLLightPosition() {
    Vector3 position = getTransform3D().getPosition();
    float lPosition[4] = { position.x, position.y, position.z, 1.0 };
    glLightfv( getLightNumber(), GL_POSITION, lPosition );
}

void Light::enable() {
    glEnable(getLightNumber());
}

GLuint Light::getLightNumber() {
    return light_number;
}

Transform3D& Light::getTransform3D() {
    return transform_3D;
}

Color Light::getDiffuseColor() {
    return diffuse;
}

Color Light::getAmbientColor() {
    return ambient;
}

void Light::figureOutLightNumber() {
    // Use the static light_number to get this Light's personal light number.
    // (GL_LIGHT0, GL_LIGHT1, ...)
    // GLboolean isTrue;
    // glGetBooleanv(GL_LIGHT0, &isTrue);
    light_number = global_light_number;
    global_light_number++;
}
