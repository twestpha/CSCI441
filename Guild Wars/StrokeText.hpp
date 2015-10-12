#ifndef StrokeText_h
#define StrokeText_h

#include <string>

#include "gl_includes.hpp"

#include "Color.hpp"
#include "Point.hpp"

using namespace std;

class StrokeText {
public:

    static void glutStrokeString(void* font, string to_draw);
    static void drawStringInWorld(string to_draw, Color color, Point position, float line_width);

private:

};

#endif
