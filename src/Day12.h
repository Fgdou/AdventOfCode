//
// Created by fgdou on 12/12/22.
//

#ifndef ADVENTOFCODE2022_DAY12_H
#define ADVENTOFCODE2022_DAY12_H


#include <vector>
#include "abstract.h"
#include "v2.h"

using namespace std;

class Day12 : public Abstract {
private:
    struct Input{
        vector<vector<char>> map;
        v2 start;
        v2 end;
    };
    Input input;
public:
    void parse(std::istream &in) override;

    void solve() override;

    bool check(v2 pos, v2 last, const vector<vector<int>>& counts);

    vector<v2> aStar();
};


#endif //ADVENTOFCODE2022_DAY12_H
