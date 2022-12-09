//
// Created by fgdou on 12/9/22.
//

#ifndef ADVENTOFCODE2022_DAY9_H
#define ADVENTOFCODE2022_DAY9_H


#include <vector>
#include <set>
#include <map>
#include "abstract.h"
#include "v2.h"

using namespace std;

class Day9 : public Abstract {
private:
    map<char, v2> dirs{
            {'R', {1, 0}},
            {'L', {-1, 0}},
            {'U', {0, -1}},
            {'D', {0, 1}}
    };

    struct Command {
        char dir;
        int n;
    };

    class Board{
        set<v2> tailVisited;
        vector<v2> body;

    public:
        Board(int n);

        void move(const v2& dir);
        int cntTailVisited() const;

        static bool isTooFar(const v2& v1, const v2& v2, int n);

        void print(const v2& start, const v2& stop) const;

    private:
        void move(int n, const v2& dir);
        v2 getMove(const v2& target, const v2& from);
    };

    vector<Command> input;
public:
    void parse(std::istream &in) override;

    void solve() override;

private:
    vector<v2> convertMoves(const vector<Command>& input);
};


#endif //ADVENTOFCODE2022_DAY9_H
