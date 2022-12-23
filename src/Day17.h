//
// Created by fgdou on 23/12/22.
//
// 20h30

#ifndef ADVENTOFCODE2022_DAY17_H
#define ADVENTOFCODE2022_DAY17_H


#include "abstract.h"
#include "v2.h"

#include <vector>
#include <map>
#include <set>

#define WIDTH 7
#define START_X 2
#define START_Y 3

using namespace std;

class Day17 : public Abstract {
private:

    string input;

    class Flow{
        string flow;
        int n;
    public:
        explicit Flow(string flow);
        char getNext();
        int count() const;
    };

    class Rock{
        v2 bottomLeft;
        vector<v2> poses;

        static vector<vector<v2>> s_poses;
    public:
        Rock(v2 bottomLeft, int type);

        bool intersect(const set<v2>& other) const;

        v2 getBottomLeft() const;
        v2 getTopRight() const;

        void move(const v2& delta);

        void print(vector<vector<char>>& tab, char c) const;

        static int countRockType();

        vector<v2> getPoses() const;
    };
    class Tunnel{
        set<v2> rocks;
        Flow flow;
        int top;

    public:
        explicit Tunnel(Flow flow);

        int getTop() const;

        void fall(int rockType);

        bool isValidPos(const v2& pos) const;
        bool intersect(const Rock& rock) const;

        bool moveRock(Rock& rock, v2 dir) const;

        void print(const Rock& r) const;

        int goDown(const v2& pos, int dir);
    };

public:
    void parse(std::istream &in) override;

    void solve() override;

};


#endif //ADVENTOFCODE2022_DAY17_H
