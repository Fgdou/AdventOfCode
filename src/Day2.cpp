//
// Created by fgdou on 12/2/22.
//

#include "Day2.h"
#include <iostream>
#include <sstream>

using namespace std;

void Day2::parse(std::istream &in) {
    input.clear();
    while(!in.eof()){
        string line;
        getline(in, line);

        if(line.empty())
            continue;

        istringstream is(line);

        Line i{};
        is >> i.opponent >> i.me;

        if(!(i.opponent >= 'A' && i.opponent <= 'C'))
            throw runtime_error("Invalid char " + to_string(i.opponent) + " line " + to_string(input.size()));
        if(!(i.me >= 'X' && i.me <= 'Z'))
            throw runtime_error("Invalid char " + to_string(i.me) + " line " + to_string(input.size()));

        input.emplace_back(i);
    }
}


vector<Day2::Info> Day2::getScores(const Input& in){
    vector<Info> out;
    for(auto& l : in){
        Info i{};
        string g = string(1, l.opponent)+l.me;
        i.win = winMap[g];
        i.score = myScore[l.me] + scoreWin[i.win];
        out.emplace_back(i);
    }
    return out;
}

int Day2::totalScore(const vector<Info>& game){
    int n = 0;
    for(auto& l : game){
        n += l.score;
    }
    return n;
}

void Day2::solve() {
    auto game = getScores(input);
    auto score = totalScore(game);

    cout << "Part 1 : " << score << endl;

    auto newGame = findWayTo(input);
    auto scores = getScores(newGame);
    auto score2 = totalScore(scores);

    cout << "Part 2 : " << score2 << endl;
}

Day2::Input Day2::findWayTo(const Input &game) {
    Input out;
    for(auto& l : game){
        string g = string(1, l.opponent) + string(1, l.me);
        out.push_back({
                                 l.opponent,
                                 wayToWinMap[g]
                         });
    }
    return out;
}
