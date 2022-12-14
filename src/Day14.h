//
// Created by fgdou on 12/14/22.
//

// 7h50
// 8H56

#ifndef ADVENTOFCODE2022_DAY14_H
#define ADVENTOFCODE2022_DAY14_H


#include <vector>
#include <map>
#include "abstract.h"
#include "v2.h"

using namespace std;

class Day14 : public Abstract {
private:
    vector<vector<v2>> input;


    class Line {
    private:
        vector<v2> points;
        vector<v2> allPoints;
    public:
        Line(vector<v2> points);
        bool isIn(const v2& v) const;

        int getYMax() const;

    private:
        vector<v2> getPoints() const;
    };
    class Floor {
    public:
        enum class Type {
            EMPTY,
            SAND,
            WALL
        };
    private:
        vector<v2> sand;
        vector<Line> lines;
        int floor;

    public:
        Floor(vector<Line> lines);

        Type get(const v2& pos) const;
        void setSand(const v2& pos);

        int countSand() const;

        int getFloor() const;
    };
public:
    const int START = 500;
    const int MAX = 300;

    void parse(std::istream &in) override;

    void solve() override;

private:
    vector<Line> getLines(const vector<vector<v2>>& vec);
    bool sandFall(Floor& f);
    void sandFallRecurse(Floor& f, const v2& pos);
};


#endif //ADVENTOFCODE2022_DAY14_H
