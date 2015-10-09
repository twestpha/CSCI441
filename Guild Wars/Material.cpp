#include "Material.hpp"

Material::Material(Color diffuse, Color specular, Color ambient) : diffuse(diffuse), specular(specular), ambient(ambient) {

}

void Material::apply() {
    float diffuse_array[4] = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_array);

    float specular_array[4] = {specular.r, specular.g, specular.b, specular.a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_array);

    float ambient_array[4] = {ambient.r, ambient.g, ambient.b, ambient.a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_array);

}
