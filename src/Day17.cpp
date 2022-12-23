//
// Created by fgdou on 23/12/22.
//

#include <iostream>
#include <algorithm>
#include "Day17.h"

vector<vector<v2>> Day17::Rock::s_poses{
        {
                {0, 0},
                {1, 0},
                {2, 0},
                {3, 0}
        },{
                {1, 0},
                {0, 1},
                {1, 1},
                {2, 1},
                {1, 2}
        },{
                {0, 0},
                {1, 0},
                {2, 0},
                {2, 1},
                {2, 2}
        },{
                {0, 0},
                {0, 1},
                {0, 2},
                {0, 3}
        },{
                {0, 0},
                {0, 1},
                {1, 0},
                {1, 1}
        }
};

void Day17::parse(std::istream &in) {
    getline(in, input);
}

void Day17::solve() {
    Flow f(input);
    Tunnel t(f);

    int rockType = 0;
    long max = 2022;

    for(long i=0; i<max; i++){
        t.fall(rockType);
        rockType = (rockType+1) % Rock::countRockType();
    }
    cout << t.getTop() << endl;
}

Day17::Rock::Rock(v2 bottomLeft, int type)
    : bottomLeft(bottomLeft), poses(s_poses[type])
{

}

v2 Day17::Rock::getBottomLeft() const {
    return bottomLeft;
}

v2 Day17::Rock::getTopRight() const {
    v2 m = poses[0];

    for(auto& p : poses){
        auto pos = p;
        m = {
                max(m.x, pos.x),
                max(m.y, pos.y)
        };
    }

    return m+bottomLeft;
}

void Day17::Rock::move(const v2 &delta) {
    bottomLeft += delta;
}

void Day17::Rock::print(vector<vector<char>> &tab, char c) const {
    for(auto& p : poses){
        auto pos = p+bottomLeft;
        tab[pos.y][pos.x] = c;
    }
}

int Day17::Rock::countRockType() {
    return s_poses.size();
}

bool Day17::Rock::intersect(const set<v2> &other) const {
    for(auto& p : poses){
        auto pos = p+bottomLeft;
        if(other.find(pos) != other.end())
            return true;
    }
    return false;
}

vector<v2> Day17::Rock::getPoses() const {
    vector<v2> res;
    for(auto& p : poses){
        res.push_back(p + bottomLeft);
    }
    return res;
}

int Day17::Tunnel::getTop() const {
    return top;
}

bool Day17::Tunnel::isValidPos(const v2 &pos) const {
    return pos.x >= 0 && pos.x < WIDTH && pos.y >= 0;
}

bool Day17::Tunnel::intersect(const Day17::Rock &rock) const {
    if(rock.getTopRight().y < 0)
        return true;
    if(rock.intersect(rocks))
        return true;
    return false;
}

void Day17::Tunnel::fall(int rockType) {
    v2 initPos{
        START_X,
        getTop()+START_Y
    };
    Rock rock(initPos, rockType);

    while(true){
        // move with flow
        char c = flow.getNext();
        v2 dir = (c == '<') ? v2{-1, 0} : v2{1, 0};
        moveRock(rock, dir);


        // move down and lock
        dir = {0, -1};
        if(!moveRock(rock, dir))
            break;

    }
    // add rock
    auto poses = rock.getPoses();
    for(auto& p : poses){
        rocks.insert(p);
        top = max(top, p.y+1);
    }
}

Day17::Tunnel::Tunnel(Day17::Flow flow)
    : flow(std::move(flow)), top(0)
{

}

bool Day17::Tunnel::moveRock(Day17::Rock &rock, v2 dir) const {
    auto tr = rock.getTopRight();
    auto bl = rock.getBottomLeft();

    if(!isValidPos(tr+dir) || !isValidPos(bl+dir))
        return false;
    rock.move(dir);
    if(intersect(rock)){
        rock.move(dir*-1);
        return false;
    }

    return true;
}

void Day17::Tunnel::print(const Rock& r) const {
    v2 tr {
            7,
            getTop()+START_Y+5
    };


    vector<vector<char>> tab(tr.y);
    for(auto& v : tab)
        v.resize(tr.x);

    for(auto& p : rocks)
        tab[p.y][p.x] = '#';

    r.print(tab, '@');

    for(int y=tr.y-1; y>=0; y--){
        cout << "|";
        for(int x=0; x<tr.x; x++){
            cout << ((tab[y][x] == 0) ? ' ' : tab[y][x]);
        }
        cout << "|" << endl;
    }
    cout << '+';
    for(int x=0; x<tr.x; x++){
        cout << '-';
    }
    cout << '+' << endl;

}
int Day17::Tunnel::goDown(const v2& pos, int dir) {
    if(pos.x <= 0 || pos.x >= 6)
        return pos.y;
    if(rocks.find(pos) == rocks.end())
        return -1;

    int v;

    v = goDown(pos + v2{dir, 0}, dir);
    if(v == -1)
        v = goDown(pos + v2{dir, -1}, dir);
    if(v == -1)
        v = goDown(pos + v2{0, -1}, dir);

    return v;
}

Day17::Flow::Flow(string flow)
    : flow(std::move(flow)), n(0)
{

}

char Day17::Flow::getNext() {
    char c = flow[n];
    n = (n+1)%flow.size();
    return c;
}

int Day17::Flow::count() const {
    return flow.size();
}
