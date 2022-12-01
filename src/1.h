//
// Created by fgdou on 12/1/22.
//

#ifndef ADVENTOFCODE2022_1_H
#define ADVENTOFCODE2022_1_H

#include "abstract.h"
#include <vector>

using namespace std;
class Day1 : public Abstract {
public:
    Day1() = default;
    ~Day1() override = default;

    void parse(std::istream &in) override;

    void solve() override;
private:
};

#endif //ADVENTOFCODE2022_1_H
