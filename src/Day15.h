//
// Created by fgdou on 12/15/22.
//
// 10h15

#ifndef ADVENTOFCODE2022_DAY15_H
#define ADVENTOFCODE2022_DAY15_H


#include <vector>
#include <memory>
#include "abstract.h"
#include "v2.h"

using namespace std;
class Day15 : public Abstract {
private:
    class Beacon {
        v2 pos;
    public:
        explicit Beacon(const v2 &pos);

        const v2 &getPos() const;
    };
    class Sensor {
        v2 pos;
        Beacon beacon;
    public:
        const v2 &getPos() const;

        const Beacon &getBeacon() const;

        bool isInRange(const v2& other) const;
        int getRange() const;

        Sensor(const v2 &pos, Day15::Beacon beacon);
    };

    class Map{
        vector<Sensor> sensors;
        v2 minPos;
        v2 maxPos;
    public:
        void addSensor(const Sensor& s);
        int countCoverage(int line) const;
        v2 findPossible(int max) const;
    private:
        bool isTaken(const v2 &pos) const;
    };

    Map input;
public:
    void parse(std::istream &in) override;

    void solve() override;
};


#endif //ADVENTOFCODE2022_DAY15_H
