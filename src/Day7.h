//
// Created by fgdou on 12/7/22.
//

#ifndef ADVENTOFCODE2022_DAY7_H
#define ADVENTOFCODE2022_DAY7_H


#include <vector>
#include <map>
#include "abstract.h"
#include <memory>

using namespace std;

class Day7 : public Abstract {
private:
    struct Dir{
    private:
        map<string, int> files;
        map<string, shared_ptr<Dir>> dirs;
        int size = -1;
    public:
        Dir() = default;
        void addFile(const string& s, int size);
        void addDir(const string& s, shared_ptr<Dir>& ptr);
        Dir& getDir(const string& s);

        int getSize();

        int countMoreThan(int n, bool first = true);
        int free(int size);

        ostream& print(ostream& os, const string &depth = "");
    };

    shared_ptr<Dir> input;

public:
    void parse(std::istream &in) override;

    void solve() override;
};

#endif //ADVENTOFCODE2022_DAY7_H
