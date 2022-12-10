//
// Created by fgdou on 12/10/22.
//

// 7:30
// 8:00

#ifndef ADVENTOFCODE2022_DAY10_H
#define ADVENTOFCODE2022_DAY10_H


#include <vector>
#include "abstract.h"

#include <memory>
#include <map>

using namespace std;
class Day10 : public Abstract {
private:
    class Command {
    public:
        virtual void execute(map<char, int> &registers) = 0;
        virtual bool done() = 0;
    };
    vector<int> cycles {
            20, 60, 100, 140, 180, 220
    };

    class Noop : public Command {
    private:
        bool d = false;
    public:
        void execute(map<char, int> &registers) override;

        bool done() override;
    };
    class Add : public Command {
    private:
        int n;
        char c;
        int ncycles = 2;
    public:
        Add(int n, char c);
        void execute(map<char, int> &registers) override;

        bool done() override;
    };


    vector<shared_ptr<Command>> input;

public:
    void parse(istream &in) override;

    void solve() override;

private:

};


#endif //ADVENTOFCODE2022_DAY10_H
