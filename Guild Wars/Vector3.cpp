#include "Vector3.hpp"

Vector3::Vector3(Point a, Point b) {
    x = a.getX() - b.getX();
    y = a.getY() - b.getY();
    z = a.getZ() - b.getZ();
}

Vector3 Vector3::difference(Point a, Point b) {
	return Vector3(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}
