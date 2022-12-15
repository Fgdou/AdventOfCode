//
// Created by fgdou on 12/9/22.
//

#include "v2.h"
#include <cmath>

v2::v2()
    : x(0), y(0)
{

}

v2::v2(int x, int y)
    : x(x), y(y)
{

}

v2::v2(int n)
    : x(n), y(n)
{

}

v2 &v2::operator=(const v2 &other) = default;

bool v2::operator==(const v2 &other) const {
    return x == other.x && y == other.y;
}

v2 &v2::operator+=(const v2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

v2 &v2::operator-=(const v2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

v2 &v2::operator/=(const v2 &other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

v2 &v2::operator*=(const v2 &other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

v2 v2::operator+(const v2 &other) const {
    v2 add = *this;
    add += other;
    return add;
}
v2 v2::operator-(const v2 &other) const {
    v2 add = *this;
    add -= other;
    return add;
}

v2 v2::operator*(const v2 &other) const {
    v2 add = *this;
    add *= other;
    return add;
}

v2 v2::operator/(const v2 &other) const {
    v2 add = *this;
    add /= other;
    return add;
}

bool v2::operator<(const v2 &other) const {
    if(x == other.x)
        return y < other.y;
    return x < other.x;
}

int v2::manhattanDistance(const v2 &other) const {
    return abs(x - other.x) + abs(y - other.y);
}

double v2::distance(const v2 &other) const {
    v2 delta = other-*this;
    return sqrt(delta.x*delta.x + delta.y*delta.y);
}

bool v2::operator!=(const v2 &other) const {
    return !(*this == other);
}

v2 v2::rotate(double r) const {
    int xx = cos(r)*x - sin(r)*y;
    int yy = sin(r)*x + sin(r)*y;

    return {xx, yy};
}


std::ostream &operator<<(std::ostream &os, const v2 &v) {
    os << '{' << v.x << ", " << v.y << '}';
    return os;
}
