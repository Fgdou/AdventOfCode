//
// Created by fgdou on 12/5/22.
//

// 9:13

#ifndef ADVENTOFCODE2022_DAY5_H
#define ADVENTOFCODE2022_DAY5_H

#include <stack>
#include <vector>
#include "abstract.h"

using namespace std;
class Day5 : public Abstract {
private:
    struct Action{
        int from, to;
        int number;
    };
    struct Input{
        vector<stack<char>> piles;
        vector<Action> actions;
    };
    Input input;
public:
    void parse(std::istream &in) override;

    void solve() override;
private:
    void move(vector<stack<char>>& piles, int from, int to);
    void executeAction(vector<stack<char>>& piles, const Action& action);
    void moveWithOrder(vector<stack<char>>& piles, const Action& action);
    string getTop(vector<stack<char>>& piles);
};


#endif //ADVENTOFCODE2022_DAY5_H
