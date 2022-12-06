//
// Created by fgdou on 12/6/22.
//

#ifndef ADVENTOFCODE2022_DAY6_H
#define ADVENTOFCODE2022_DAY6_H


#include "abstract.h"

using namespace std;

class Day6 : public Abstract {
private:
    string input;
    int n = 14;
public:
    void parse(std::istream &in) override;

    void solve() override;
private:
    int getFirst(const string& input);
    bool hasDouble(const map<char, int>& m);
};


#endif //ADVENTOFCODE2022_DAY6_H
