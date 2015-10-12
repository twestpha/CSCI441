#ifndef HeroNameDrawer_h
#define HeroNameDrawer_h

#include <string>

#include "gl_includes.hpp"

#include "Transform3D.hpp"
#include "Color.hpp"
#include "Point.hpp"

using namespace std;

class HeroNameDrawer {
public:
    HeroNameDrawer(Transform3D& hero_transform, string name);

    void draw();

    Transform3D& getHeroTransform();
    string getName();

private:
    void glutStrokeString(void* font, string to_draw);
    void drawStringInWorld(string to_draw, Color color, Point position, float line_width);

    Transform3D& hero_transform;
    string name;


};

#endif
