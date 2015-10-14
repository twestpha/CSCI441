#ifndef HeroNameDrawer_h
#define HeroNameDrawer_h

#include <string>

#include "Transform3D.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "StrokeText.hpp"
#include "HeroBase.hpp"

using namespace std;

class HeroNameDrawer {
public:
    HeroNameDrawer(Transform3D& hero_transform, Color color, string name);
    HeroNameDrawer(HeroBase& hero_base);

    void draw();

    Transform3D& getHeroTransform();
    string getName();

private:
    Transform3D& hero_transform;
    string name;
    Color color;

};

#endif
