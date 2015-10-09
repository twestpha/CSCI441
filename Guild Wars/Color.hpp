#ifndef Color_h
#define Color_h

struct Color {
    Color() : r(0), g(0), b(0), a(1) {;}
    Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {;}
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {;}

    float r;
    float g;
    float b;
    float a;
};

#endif
