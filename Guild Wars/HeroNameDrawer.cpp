#include "HeroNameDrawer.hpp"

HeroNameDrawer::HeroNameDrawer(Transform3D& hero_transform, Color color, string name) : hero_transform(hero_transform), color(color), name(name) {

}

HeroNameDrawer::HeroNameDrawer(HeroBase& hero, Color color) : hero_transform(hero.getTransform()), color(color), name(hero.getName()) {

}

void HeroNameDrawer::draw() {
    float boldness = 2;

    float height_offset = 7;
    Vector3 hero_position = getHeroTransform().getPosition();
	Point point_to_draw_at(hero_position.x, hero_position.y + height_offset, hero_position.z);

	glDisable(GL_LIGHTING);
	StrokeText::drawStringInWorld(getName(), getColor(), point_to_draw_at, boldness);
	glEnable(GL_LIGHTING);
}

Transform3D& HeroNameDrawer::getHeroTransform() {
    return hero_transform;
}

Color HeroNameDrawer::getColor() {
    return color;
}

string HeroNameDrawer::getName() {
    return name;
}
