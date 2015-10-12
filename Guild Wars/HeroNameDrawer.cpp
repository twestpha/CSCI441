#include "HeroNameDrawer.hpp"

HeroNameDrawer::HeroNameDrawer(Transform3D& hero_transform, string name) : hero_transform(hero_transform), name(name) {

}

void HeroNameDrawer::draw() {
    Color krandul_color(0.2, 0.18, 1.0);
    float boldness = 3;

    Vector3 hero_position = getHeroTransform().getPosition();
	Point point_to_draw_at(hero_position.x, hero_position.y, hero_position.z);

	glDisable(GL_LIGHTING);
	StrokeText::drawStringInWorld(getName(), krandul_color, point_to_draw_at, boldness);
	glEnable(GL_LIGHTING);
}

Transform3D& HeroNameDrawer::getHeroTransform() {
    return hero_transform;
}

string HeroNameDrawer::getName() {
    return name;
}
