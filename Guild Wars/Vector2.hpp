// Vector2
//      I got tired of using two floats for everything so I made a Vector2 class. You can do basic math operations on it and get the magnitude and unit vector. It's very useful.
#ifndef Vector2_h
#define Vector2_h

#include <cmath>

// Simple struct to act as a vector in 2D space.
struct Vector2 {
    Vector2() : Vector2(0, 0) {;}
    Vector2(float x, float y) : x(x), y(y) {

    }

    // Vector2 + Vector2
    Vector2 operator+(const Vector2& rhs) {
        Vector2 sum = *this;
        sum.x += rhs.x;
        sum.y += rhs.y;
        return sum;
    }

    // Vector2 - Vector2
    Vector2 operator-(const Vector2& rhs) {
        Vector2 sum = *this;
        sum.x -= rhs.x;
        sum.y -= rhs.y;
        return sum;
    }

    // Vector2 / float
    Vector2 operator/(const float rhs) {
        Vector2 result = *this;
        result.x /= rhs;
        result.y /= rhs;
        return result;
    }

    // Vector2 * float
    Vector2 operator*(const float rhs) {
        Vector2 result = *this;
        result.x *= rhs;
        result.y *= rhs;
        return result;
    }

    // Vector2 (dot) Vector2
    float dot(const Vector2& rhs) {
        return ((this->x * rhs.x) + (this->y * rhs.y));
    }

    // Vector2 (cross) Vector2
    Vector2 cross(const Vector2& rhs) {
        Vector2 result = *this;

        return result;
    }

    float magnitude() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    Vector2 unit() {
        Vector2 result = *this;
        float magnitude = result.magnitude();
        result.x /= magnitude;
        result.y /= magnitude;

        return result;
    }

    float x, y;
};

#endif
