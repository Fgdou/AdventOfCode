//
// Created by fgdou on 12/11/22.
//

// 10:27
// 11:42
// 16:45
// 17:00
//

#ifndef ADVENTOFCODE2022_DAY11_H
#define ADVENTOFCODE2022_DAY11_H

#include <vector>
#include "abstract.h"

using namespace std;
class Day11 : public Abstract {
private:
    struct Item{
    private:
        long value;
    public:
        explicit Item(long n);
        void add(const Item &n);
        void mul(const Item &n);
        void div(int n);

        long getValue() const;

        bool modulus(int n) const;

        void doModulus(long i);
    };
    struct Monkey{
        vector<Item> items;
        char operation;
        long operationNumber;
        int condition;
        int monkeyTrue;
        int monkeyFalse;

        void moveItems(vector<Monkey> &monkeys, long modulus);

        int getCountItems() const;

        void print(int n) const;

    private:
        int countItems = 0;
        int check(const Item &item) const;
        void calcOperation(Item &item) const;
    };

    vector<Monkey> input;

public:
    void parse(istream &in) override;

    void solve() override;

private:
    void round(vector<Monkey> &monkeys, long modulus);

    int checkItem(int item, Monkey &monkey);
    vector<int> countItems(const vector<Monkey>& monkeys);
    void printAll(const vector<Monkey> &monkeys, int round);

    long bigModulus(const vector<Monkey>& Monkey);
};


#endif //ADVENTOFCODE2022_DAY11_H
