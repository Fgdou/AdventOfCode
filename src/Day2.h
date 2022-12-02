//
// Created by fgdou on 12/2/22.
//

// 15587

#ifndef ADVENTOFCODE2022_DAY2_H
#define ADVENTOFCODE2022_DAY2_H


#include "abstract.h"
#include <map>
#include <vector>

using namespace std;

class Day2 : public Abstract {
private:
    struct Line {
        char opponent;
        char me;
    };
    using Input = vector<Line>;

    Input input;

    enum Win {
        WIN,
        LOOSE,
        TIE
    };
    map<char, int> myScore{
            {'X', 1},
            {'Y', 2},
            {'Z', 3}
    };
    map<string, Win> winMap{
            {"AX", TIE},
            {"AY", WIN},
            {"AZ", LOOSE},
            {"BX", LOOSE},
            {"BY", TIE},
            {"BZ", WIN},
            {"CX", WIN},
            {"CY", LOOSE},
            {"CZ", TIE},
    };
    map<string, char> wayToWinMap{
            {"AX", 'Z'},
            {"AY", 'X'},
            {"AZ", 'Y'},
            {"BX", 'X'},
            {"BY", 'Y'},
            {"BZ", 'Z'},
            {"CX", 'Y'},
            {"CY", 'Z'},
            {"CZ", 'X'},
    };
    map<Win, int> scoreWin{
            {WIN, 6},
            {TIE, 3},
            {LOOSE, 0}
    };
    struct Info{
        Win win;
        int score;
    };
public:
    void parse(std::istream &in) override;

    void solve() override;

private:
    vector<Info> getScores(const Input& in);
    int totalScore(const vector<Info>& game);
    Input findWayTo(const Input &game);
};


#endif //ADVENTOFCODE2022_DAY2_H
