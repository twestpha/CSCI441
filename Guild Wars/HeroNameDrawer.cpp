#include "HeroNameDrawer.hpp"

HeroNameDrawer::HeroNameDrawer(Transform3D& hero_transform, string name) : hero_transform(hero_transform), name(name) {

}

void HeroNameDrawer::draw() {
    Color krandul_color(0.2, 0.18, 1.0);
    float boldness = 3;

    Vector3 hero_position = getHeroTransform().getPosition();
	Point point_to_draw_at(hero_position.x, hero_position.y, hero_position.z);


	glDisable(GL_LIGHTING);
	drawStringInWorld(getName(), krandul_color, point_to_draw_at, boldness);
	glEnable(GL_LIGHTING);
}

Transform3D& HeroNameDrawer::getHeroTransform() {
    return hero_transform;
}

string HeroNameDrawer::getName() {
    return name;
}

void HeroNameDrawer::glutStrokeString(void* font, string to_draw) {
    for (int i = 0; i < to_draw.size(); ++i) {
        glutStrokeCharacter(font, to_draw[i]);
    }
}

void HeroNameDrawer::drawStringInWorld(string to_draw, Color color, Point position, float line_width) {
    glRasterPos3f(0, 0, 0);
	glLineWidth(line_width);
	glColor4f(color.r, color.g, color.b, color.a);
	glTranslatef(position.getX(), position.getY(), position.getZ());
	glScalef(0.01, 0.01, 0.01);

    void* default_stroke_font = GLUT_STROKE_ROMAN;
    glutStrokeString(default_stroke_font, to_draw);
}
