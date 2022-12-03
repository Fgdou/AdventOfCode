//
// Created by fgdou on 12/3/22.
//

#ifndef ADVENTOFCODE2022_DAY3_H
#define ADVENTOFCODE2022_DAY3_H

#include <vector>
#include <map>
#include "abstract.h"
#include <set>

using namespace std;

class Day3 : public Abstract {
private:
    using Input = vector<string>;

    struct Backpack {
        string left;
        string right;
    };

    Input input;
public:
    void parse(std::istream &in) override;

    void solve() override;
private:
    int getPriority(char c);
    vector<char> sortPriorities(const map<char, int>& m);
    map<char, int> getPriorities(const set<char>& chars);
    vector<Backpack> separate(const Input& in);
    set<char> getCommon(const string& a, const string& b);
    vector<vector<string>> getGroups(const Input& in);
    char getCommon(const vector<string>& strs);
};


#endif //ADVENTOFCODE2022_DAY3_H
