//
// Created by fgdou on 12/9/22.
//

#ifndef ADVENTOFCODE2022_V2_H
#define ADVENTOFCODE2022_V2_H


#include <ostream>

class v2 {
public:
    int x, y;

    v2();
    v2(const v2& other) = default;
    v2(int x, int y);
    v2(int n);

    bool operator==(const v2& other) const;
    bool operator!=(const v2& other) const;
    v2& operator=(const v2& other);
    v2& operator+=(const v2& other);
    v2& operator-=(const v2& other);
    v2& operator/=(const v2& other);
    v2& operator*=(const v2& other);
    v2 operator+(const v2& other) const;
    v2 operator-(const v2& other) const;
    v2 operator/(const v2& other) const;
    v2 operator*(const v2& other) const;

    bool operator<(const v2& other) const;

    int manhattanDistance(const v2& other) const;
    double distance(const v2& other) const;

    v2 rotate(double r) const;
};

std::ostream& operator<<(std::ostream& os, const v2& v);


#endif //ADVENTOFCODE2022_V2_H
