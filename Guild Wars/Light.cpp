#include "Light.hpp"

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
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseCol );

    float ambientCol[4] = {
        getAmbientColor().r,
        getAmbientColor().g,
        getAmbientColor().b,
        1.0
    };
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
}

void Light::setGLLightPosition() {
    Vector3 position = getTransform3D().getPosition();
    float lPosition[4] = { position.x, position.y, position.z, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, lPosition );
}

void Light::enable() {
    glEnable(getLightNumber());
}

GLuint Light::getLightNumber() {
    return GL_LIGHT0;
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
}
