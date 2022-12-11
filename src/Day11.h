//
// Created by fgdou on 12/11/22.
//

// 10:27

#ifndef ADVENTOFCODE2022_DAY11_H
#define ADVENTOFCODE2022_DAY11_H

#include <vector>
#include "abstract.h"

using namespace std;
class Day11 : public Abstract {
private:
    struct Monkey{
        vector<int> items;
        char operation;
        long operationNumber;
        int condition;
        int monkeyTrue;
        int monkeyFalse;

        void moveItems(vector<Monkey> &monkeys);

        int getCountItems() const;

        void print(int n) const;

    private:
        int countItems = 0;
        int check(long item) const;
        long calcOperation(int item) const;
    };

    vector<Monkey> input;

public:
    void parse(istream &in) override;

    void solve() override;

private:
    void round(vector<Monkey> &monkeys);

    int checkItem(int item, Monkey &monkey);
    vector<int> countItems(const vector<Monkey>& monkeys);
    void printAll(const vector<Monkey> &monkeys, int round);
};


#endif //ADVENTOFCODE2022_DAY11_H
