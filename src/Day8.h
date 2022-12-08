//
// Created by fgdou on 12/8/22.
//

// 8:07
// 8:43

#ifndef ADVENTOFCODE2022_DAY8_H
#define ADVENTOFCODE2022_DAY8_H


#include <vector>
#include "abstract.h"

using namespace std;
class Day8 : public Abstract {
private:
    using Input = vector<vector<int>>;
    using Visible = vector<vector<bool>>;
    Input input;
public:
    void parse(std::istream &in) override;

    void solve() override;

private:
    void print(const Visible& v);
    bool isValid(int x, int y, const Input &input);
    void check(int x, int y, int dx, int dy, const Input& in, Visible& v);
    int check(int x, int y, int dx, int dy, const Input& in, int base);
    int count(const Visible& v);
};


#endif //ADVENTOFCODE2022_DAY8_H
