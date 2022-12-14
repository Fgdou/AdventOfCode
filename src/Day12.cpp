//
// Created by fgdou on 12/12/22.
//

#include <stack>
#include "Day12.h"
#include "v2.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include "utils.h"

void Day12::parse(std::istream &in) {
    Input i{};

    v2 pos;
    while(!in.eof()){
        pos.x = 0;
        i.map.emplace_back();

        string line;
        getline(in, line);

        for(char c : line){
            i.map[pos.y].emplace_back(c);

            if(c == 'S')
                i.start = pos;
            else if(c == 'E')
                i.end = pos;

            pos.x++;
        }
        pos.y++;
    }
    input = i;
}

void Day12::solve() {
    auto path = aStar();
    cout << "Part 1 : " << path.size()-1 << endl;
    auto path2 = aStar2();
    cout << "Part 2 : " << path2.size()-1 << endl;
}

vector<v2> Day12::aStar() {
    vector<vector<int>> count(input.map.size());
    vector<vector<v2>> last(input.map.size());

    // Resize maps
    for(auto& v : count)
        v.resize(input.map[0].size());
    for(auto& v : last)
        v.resize(input.map[0].size());

    vector<v2> toVisit;

    toVisit.push_back(input.start);

    bool endFinded = false;

    // Visit everything
    while(!toVisit.empty()){

        v2 pos = toVisit[0];
        if(pos == input.end)
            endFinded = true;
        toVisit.erase(toVisit.begin());
        std::sort(toVisit.begin(), toVisit.end(), [&](v2& a, v2& b){
            return count[a.y][a.x] < count[b.y][b.x];
        });

        vector<v2> deltas = {
                {-1, 0},
                {1, 0},
                {0, -1},
                {0, 1}
        };
        for(auto& d : deltas){
            auto p = pos + d;
            if(!check(p, pos, count))
                continue;
            count[p.y][p.x] = count[pos.y][pos.x]+1;
            last[p.y][p.x] = pos;
            toVisit.push_back(p);
        }
    }


    cout << count << endl;
    if(!endFinded)
        throw runtime_error("End not found");

    // TraceBack
    vector<v2> res({input.end});

    v2 pos = input.end;
    while(true){
        pos = last[pos.y][pos.x];
        res.emplace_back(pos);

        if(pos == input.start)
            break;
    }

    std::reverse(res.begin(), res.end());

    return res;
}
vector<v2> Day12::aStar2() {
    vector<vector<int>> count(input.map.size());
    vector<vector<v2>> last(input.map.size());

    // Resize maps
    for(auto& v : count)
        v.resize(input.map[0].size());
    for(auto& v : last)
        v.resize(input.map[0].size());

    vector<v2> toVisit;

    toVisit.push_back(input.end);

    v2 end;

    // Visit everything
    while(!toVisit.empty()){

        v2 pos = toVisit[0];

        if(input.map[pos.y][pos.x] == 'a'){
            end = pos;
            break;
        }

        toVisit.erase(toVisit.begin());
        std::sort(toVisit.begin(), toVisit.end(), [&](v2& a, v2& b){
            return count[a.y][a.x] < count[b.y][b.x];
        });

        vector<v2> deltas = {
                {-1, 0},
                {1, 0},
                {0, -1},
                {0, 1}
        };
        for(auto& d : deltas){
            auto p = pos + d;
            if(!check2(p, pos, count))
                continue;
            count[p.y][p.x] = count[pos.y][pos.x]+1;
            last[p.y][p.x] = pos;
            toVisit.push_back(p);
        }
    }


    cout << count << endl;

    // TraceBack
    vector<v2> res({end});

    v2 pos = end;
    while(true){
        pos = last[pos.y][pos.x];
        res.emplace_back(pos);

        if(pos == input.end)
            break;
    }

    return res;
}

bool Day12::check(v2 pos, v2 last, const vector<vector<int>>& counts) {
    if(pos.x < 0 || pos.y < 0 || pos.x >= input.map[0].size() || pos.y >= input.map.size())
        return false;

    char newHeight = input.map[pos.y][pos.x];
    char height = input.map[last.y][last.x];

    if(height == 'S')
        height = 'a'-1;
    if(newHeight == 'E')
        newHeight = 'z'+1;

    if(newHeight > height+1)
        return false;

    int count = counts[last.y][last.x];
    int otherCount = counts[pos.y][pos.x];

    if(otherCount == 0)
        return true;

    if(count+1 < otherCount)
        return true;

    return false;
}
bool Day12::check2(v2 pos, v2 last, const vector<vector<int>>& counts) {
    if(pos.x < 0 || pos.y < 0 || pos.x >= input.map[0].size() || pos.y >= input.map.size())
        return false;

    char newHeight = input.map[pos.y][pos.x];
    char height = input.map[last.y][last.x];

    if(height == 'E')
        height = 'z';
    if(newHeight == 'S')
        newHeight = 'a';

    if(newHeight < height-1)
        return false;

    int count = counts[last.y][last.x];
    int otherCount = counts[pos.y][pos.x];

    if(otherCount == 0)
        return true;

    if(count+1 < otherCount)
        return true;

    return false;
}
