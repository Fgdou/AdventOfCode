//
// Created by fgdou on 12/15/22.
//

#include <iostream>
#include <utility>
#include <cassert>
#include "Day15.h"
#include <cmath>
#include <algorithm>

const int lines = 4000000;

void Day15::parse(std::istream &in) {
    input = {};

    while(!in.eof()){
        string line;
        getline(in, line);

        if(line.empty())
            continue;

        v2 posBeacon;
        v2 posSensor;

        sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
               &posSensor.x, &posSensor.y,
               &posBeacon.x, &posBeacon.y
               );

        Beacon b(posBeacon);
        Sensor s(posSensor, b);
        input.addSensor(s);
    }
}

void Day15::solve() {

    int count = input.countCoverage(2000000);
    cout << "Part 1 : " << count << endl;

    auto pos = input.findPossible(lines);
    cout << pos << endl;

    long frequency = ((long)pos.x) * lines + pos.y;
    cout << "Part 2 : " << frequency << endl;
}

const v2 &Day15::Sensor::getPos() const {
    return pos;
}

bool Day15::Sensor::isInRange(const v2 &other) const {
    auto range = getRange();
    auto range2 = pos.manhattanDistance(other);

    return range2 <= range;
}

const Day15::Beacon &Day15::Sensor::getBeacon() const {
    return beacon;
}

int Day15::Sensor::getRange() const {
    return pos.manhattanDistance(beacon.getPos());
}

Day15::Sensor::Sensor(const v2 &pos, Day15::Beacon beacon)
: pos(pos), beacon(std::move(beacon)) {}


Day15::Beacon::Beacon(const v2 &pos) : pos(pos) {}

const v2 &Day15::Beacon::getPos() const {
    return pos;
}

void Day15::Map::addSensor(const Day15::Sensor &s) {
    auto range = s.getRange();
    auto minRange = s.getPos()-range;
    auto maxRange = s.getPos()+range;
    if(sensors.empty()){
        minPos = minRange;
        maxPos = maxRange;
    }else{
        minPos.x = min(minPos.x, minRange.x);
        minPos.y = min(minPos.y, minRange.y);
        maxPos.x = max(maxPos.x, maxRange.x);
        maxPos.y = max(maxPos.y, maxRange.y);
    }
    sensors.push_back(s);
}

int Day15::Map::countCoverage(int line) const {
    int count = 0;
    for(int i=minPos.x; i<=maxPos.x; i++){
        v2 pos = {i, line};

        if(isTaken(pos))
            continue;
        for(auto& s : sensors){
            if(s.isInRange(pos)){
                count++;
                break;
            }
        }
    }
    return count;
}

bool Day15::Map::isTaken(const v2 &pos) const {
    for(auto& s : sensors){
        if(s.getPos() == pos)
            return true;
        if(s.getBeacon().getPos() == pos)
            return true;
    }
    return false;
}

v2 Day15::Map::findPossible(int max) const {
    return {};
}