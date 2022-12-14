//
// Created by fgdou on 12/14/22.
//

#include <iostream>
#include <utility>
#include "Day14.h"
#include <algorithm>

void Day14::parse(std::istream &in) {
    input.clear();

    while(!in.eof()){
        string line;
        getline(in, line);

        int start = 0;
        vector<v2> vecs;
        while(start < line.size()){
            int end = line.find(" -> ", start);
            if(end == -1)
                end = line.size();

            string vecString = string(line, start, end-start);
            start += vecString.size() + 4;

            v2 v;
            sscanf(vecString.c_str(), "%d,%d", &v.x, &v.y);
            vecs.push_back(v);
        }
        input.emplace_back(vecs);
    }
}

void Day14::solve() {
    auto lines = getLines(input);
    Floor f1(lines);
    Floor f2(lines);

    while(sandFall(f1)){
    }

    cout << "Part 1 (20 sec) : " << f1.countSand() << endl;

    sandFallRecurse(f2, {START, 0});

    cout << "Part 2 : " << f2.countSand() << endl;
}

vector<Day14::Line> Day14::getLines(const vector<vector<v2>> &vec) {
    vector<Line> res;

    for(auto& v : vec){
        res.emplace_back(v);
    }

    return res;
}

bool Day14::sandFall(Day14::Floor &f) {
    v2 pos = {START, 0};

    if(f.get(pos) != Floor::Type::EMPTY)
        return false;

    vector<v2> deltaTests = {
            {0, 1},
            {-1, 1},
            {1, 1}
    };

    for(int i=0; i<MAX; i++){
        bool founded = false;
        for(auto& delta : deltaTests){
            v2 newPos = pos + delta;
            if(f.get(newPos) == Floor::Type::EMPTY){
                pos = newPos;
                founded = true;
                break;
            }
        }
        if(!founded) {
            f.setSand(pos);
            return true;
        }
    }
    return false;
}

void Day14::sandFallRecurse(Day14::Floor &f, const v2 &pos) {
    vector<v2> deltaTests = {
            {0, 1},
            {-1, 1},
            {1, 1}
    };

    if(pos.y == f.getFloor())
        return;
    if(f.get(pos) != Floor::Type::EMPTY)
        return;
    f.setSand(pos);

    for(auto& delta : deltaTests){
        sandFallRecurse(f, pos+delta);
    }
}

Day14::Line::Line(vector<v2> points)
    : points(std::move(points))
{
    allPoints = getPoints();
}

vector<v2> Day14::Line::getPoints() const {
    vector<v2> pp;

    for(int i=0; i<points.size()-1; i++){
        auto p1 = points[i];
        auto& p2 = points[i+1];


        while(p1 != p2){
            pp.emplace_back(p1);
            if(p1.x < p2.x)
                p1.x++;
            if(p1.x > p2.x)
                p1.x--;
            if(p1.y < p2.y)
                p1.y++;
            if(p1.y > p2.y)
                p1.y--;
        }
        pp.emplace_back(p2);
    }

    return pp;
}

bool Day14::Line::isIn(const v2 &v) const {
    return (std::find(allPoints.begin(), allPoints.end(),v) != allPoints.end());
}

int Day14::Line::getYMax() const {
    int m = 0;

    for(auto& p : points){
        m = max(p.y, m);
    }
    return m;
}

Day14::Floor::Floor(vector<Line> lines)
    : lines(lines)
{
    int v = 0;
    for(auto& l : lines){
        v = max(l.getYMax(), v);
    }
    floor = v+2;
}

Day14::Floor::Type Day14::Floor::get(const v2 &pos) const {
    if(std::find(sand.begin(), sand.end(), pos) != sand.end())
        return Type::SAND;
    for(auto& line : lines){
        if(line.isIn(pos))
            return Type::WALL;
    }
    return Type::EMPTY;
}

void Day14::Floor::setSand(const v2 &pos) {
    sand.emplace_back(pos);
}

int Day14::Floor::countSand() const {
    return sand.size();
}

int Day14::Floor::getFloor() const {
    return floor;
}
