#ifndef Vector3_h
#define Vector3_h

#include <cmath>
#include "Point.hpp"

// Simple struct to act as a vector in 2D space.
struct Vector3 {
    Vector3() : Vector3(0, 0, 0) {;}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {

    }
    Vector3(Point a, Point b);

    // call using Vector3::up()
    static Vector3 up(){
        return Vector3(0, 1, 0);
    }

    static Vector3 down(){
        return Vector3(0, -1, 0);
    }

    static Vector3 forward(){
        return Vector3(0, 0, 1);
    }

    static Vector3 back(){
        return Vector3(0, 0, -1);
    }

    static Vector3 right(){
        return Vector3(1, 0, 0);
    }

    static Vector3 left(){
        return Vector3(-1, 0, 0);
    }

    // Vector3 + Vector3
    Vector3 operator+(const Vector3& rhs) {
        Vector3 sum = *this;
        sum.x += rhs.x;
        sum.y += rhs.y;
        sum.z += rhs.z;
        return sum;
    }

    // Vector3 - Vector3
    Vector3 operator-(const Vector3& rhs) {
        Vector3 difference = *this;
        difference.x -= rhs.x;
        difference.y -= rhs.y;
        difference.z -= rhs.z;
        return difference;
    }

    // Vector3 / float
    Vector3 operator/(const float rhs) {
        Vector3 result = *this;
        result.x /= rhs;
        result.y /= rhs;
        result.z /= rhs;
        return result;
    }

    // Vector3 * float
    Vector3 operator*(const float rhs) {
        Vector3 result = *this;
        result.x *= rhs;
        result.y *= rhs;
        result.z *= rhs;
        return result;
    }

    // Vector3 (dot) Vector3
    float dot(const Vector3& rhs) {
        return ((this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z));
    }

    // Vector3 (cross) Vector3
    Vector3 cross(const Vector3& rhs) {
        Vector3 result = *this;
        float tempX = (-1 * z * rhs.y) + (y * rhs.z);
        float tempY = (z * rhs.x) - (x * rhs.z);
        float tempZ = (-1 * y * rhs.x) + (x * rhs.y);
        result.x = tempX;
        result.y = tempY;
        result.z = tempZ;
        return result;
    }

    float magnitude() {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    Vector3 unit() {
        Vector3 result = *this;
        float magnitude = result.magnitude();
        result.x /= magnitude;
        result.y /= magnitude;
        result.z /= magnitude;

        return result;
    }

    float x, y, z;
};

#endif
