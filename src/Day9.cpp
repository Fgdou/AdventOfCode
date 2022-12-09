//
// Created by fgdou on 12/9/22.
//

#include <iostream>
#include "Day9.h"
#include <algorithm>

void Day9::parse(std::istream &in) {
    input.clear();
    while(!in.eof()){
        Command c{};
        in >> c.dir >> c.n;
        input.emplace_back(c);
    }
}

void Day9::solve() {
    auto moves = convertMoves(input);

    Board b(2);
    Board b2(10);
    v2 l{-10, -10};
    v2 r{15, 15};

//    b2.print(l, r);
    for(auto& move : moves){
        b.move(move);

        b2.move(move);
//        b2.print(l, r);
    }

    cout << "Part 1 : " << b.cntTailVisited() << endl;
    cout << "Part 2 : " << b2.cntTailVisited() << endl;
}

vector<v2> Day9::convertMoves(const vector<Command> &input) {
    vector<v2> res;
    for(auto& command : input){
        for(int i=0; i<command.n; i++){
            res.emplace_back(dirs[command.dir]);
        }
    }
    return res;
}

int Day9::Board::cntTailVisited() const {
    return tailVisited.size();
}

void Day9::Board::move(const v2 &dir) {
    move(0, dir);
}

bool Day9::Board::isTooFar(const v2 &v1, const v2 &v2, int n) {
    return abs(v1.x-v2.x) > n || abs(v1.y-v2.y) > n;
}

Day9::Board::Board(int n)
    : body(n)
{
    tailVisited.insert({0, 0});
}

void Day9::Board::print(const v2 &start, const v2 &stop) const {
    for(int y=start.y; y<=stop.y; y++) {
        for (int x = start.x; x <= stop.x; x++) {
            v2 v{x, y};

            long index = body.end() - std::find(body.begin(), body.end(),v) - 1;
            if(index != -1)
                cout << index;
            else
                cout << ((tailVisited.find(v) != tailVisited.end()) ? '#' : '.');
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Day9::Board::move(int n, const v2 &dir) {
    auto& pos = body[n];
    pos += dir;

    if(n == body.size()-1){
        tailVisited.insert(pos);
        return;
    }

    auto& tail = body[n+1];

    if(isTooFar(tail, pos, 1)){
        auto m = getMove(pos, tail);
        move(n+1, m);
    }

}

v2 Day9::Board::getMove(const v2 &target, const v2 &from) {
    v2 d;
    if(target.y == from.y)
        d = {target.x-from.x, 0};
    else if(target.x == from.x)
        d = {0, target.y-from.y};
    else
        d = target - from;

    if(d.x < -1)
        d.x = -1;
    if(d.x > 1)
        d.x = 1;
    if(d.y < -1)
        d.y = -1;
    if(d.y > 1)
        d.y = 1;

    return d;
}
