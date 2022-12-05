//
// Created by fgdou on 12/5/22.
//

#include <iostream>
#include "Day5.h"

void Day5::parse(std::istream &in) {
    input = Input{};

    vector<vector<char>> stacks;
    while(!in.eof()){
        string line;
        getline(in, line);
        if(line.empty())
            break;
        for(int i=0; i*4+1<line.size(); i++){
            char c = line[i*4+1];
            if(c != ' ') {
                if(i >= stacks.size())
                    stacks.resize(i+1);
                stacks[i].emplace_back(c);
            }
        }
    }
    input.piles.resize(stacks.size());
    for(int i=0; i<stacks.size(); i++){
        for(int j=0; j<stacks[i].size(); j++){
            input.piles[i].push(stacks[i][stacks[i].size()-1-j]);
        }
    }

    while(!in.eof()){
        Action a{};
        string line;
        getline(in, line);
        sscanf(line.c_str(), "move %d from %d to %d", &a.number, &a.from, &a.to);
        input.actions.emplace_back(a);
    }
}

void Day5::solve() {
    for(auto& action : input.actions)
        moveWithOrder(input.piles, action);

    string top = getTop(input.piles);
    cout << "Part 1 : " << top << endl;
}

void Day5::move(vector<stack<char>> &piles, int from, int to) {
    from--;
    to--;

    if(piles[from].empty())
        throw runtime_error("no more item in pile " + to_string(from+1));

    char c = piles[from].top();
    piles[from].pop();
    piles[to].push(c);
}

void Day5::executeAction(vector<stack<char>> &piles, const Day5::Action &action) {
    for(int i=0; i<action.number; i++)
        move(piles, action.from, action.to);
}

string Day5::getTop(vector<stack<char>> &piles) {
    string line{};
    for(auto& pile : piles){
        if(pile.empty())
            line += ' ';
        else
            line += pile.top();
    }
    return line;
}

void Day5::moveWithOrder(vector<stack<char>> &piles, const Day5::Action &action) {
    int from = action.from-1;
    int to = action.to-1;
    int count = action.number;

    stack<char> move;

    for (int i = 0; i < count; ++i){
        if(piles[from].empty())
            throw runtime_error("no more item in pile " + to_string(from+1));
        char c = piles[from].top();
        piles[from].pop();
        move.push(c);
    }

    while(!move.empty()){
        char c = move.top();
        move.pop();
        piles[to].push(c);
    }
}
