//
// Created by fgdou on 12/4/22.
//

#ifndef ADVENTOFCODE2022_DAY4_H
#define ADVENTOFCODE2022_DAY4_H


#include <vector>
#include "abstract.h"

using namespace std;

class Day4 : public Abstract {
private:
    struct Range{
        int left, right;

        bool contains(const Range& other) const;
        bool overlap(const Range& other) const;
    };
    struct Pair{
        Range first, second;

        bool containsEachOther() const;
        bool overlap() const;
    };

    vector<Pair> input;
public:
    void parse(std::istream &in) override;

    void solve() override;
private:
};


#endif //ADVENTOFCODE2022_DAY4_H
