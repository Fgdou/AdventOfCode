//
// Created by fgdou on 23/12/22.
//

#ifndef ADVENTOFCODE2022_DAY16_H
#define ADVENTOFCODE2022_DAY16_H


#include <map>
#include "abstract.h"
#include <set>
#include <vector>

#define START_POS "AA"
#define MAX 26

using namespace std;

class Day16 : public Abstract {
private:

    struct Input {
        map<string, int> flowrate;
        map<string, set<string>> tunnels;
    };

    struct Element {
        enum Action {
            OPEN, MOVE
        };
        string pos;
        Action action;

        static Element random(const vector<string>& possibilities);
    };
    struct Actions {
    private:
        Actions() = default;
        int count = -1;
    public:
        vector<Element> actions;
//        int evaluate(const Input &input);

        int evaluate(Actions& other, const Input &input);

        Actions randomize(double p, const Input& input) const;

        Actions generateChild(double mutation, const Input& inputs, const Actions& other) const;

        vector<Element> find(const string& pos) const;

        static Actions random(const Input& input, int minutes);

    private:
        static void fill(const Input &input, Actions &res, string &pos) ;
    };
    class Model {
        vector<Actions> population1;
        vector<Actions> population2;
        double prob;
        double mutation;
        const Input& input;
    public:
        Model(int population, double prob, double mutation, const Input& input);
        void execute();
        int getMax();

        pair<Day16::Actions&, Day16::Actions&> getProb(int total);
    };

    Input input;

public:
    void parse(std::istream &in) override;

    void solve() override;

private:
    static int countEdges(const map<string, set<string>>& tunnels);
};


#endif //ADVENTOFCODE2022_DAY16_H
