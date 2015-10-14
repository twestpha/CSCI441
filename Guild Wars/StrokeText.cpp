#include "StrokeText.hpp"

void StrokeText::glutStrokeString(void* font, string to_draw) {
    for (unsigned int i = 0; i < to_draw.size(); ++i) {
        glutStrokeCharacter(font, to_draw[i]);
    }
}

void StrokeText::drawStringInWorld(string to_draw, Color color, Point position, float line_width) {
    glRasterPos3f(0, 0, 0);
	glLineWidth(line_width);

    glPushMatrix();
        glColor4f(color.r, color.g, color.b, color.a);
        glTranslatef(position.getX(), position.getY(), position.getZ());
    	glScalef(0.01, 0.01, 0.01);
        void* default_stroke_font = GLUT_STROKE_ROMAN;
        glutStrokeString(default_stroke_font, to_draw);
    glPopMatrix();
}
