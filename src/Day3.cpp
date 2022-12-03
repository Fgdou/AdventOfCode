//
// Created by fgdou on 12/3/22.
//

#include <set>
#include <iostream>
#include "Day3.h"
#include <algorithm>

void Day3::parse(std::istream &in) {
    input.clear();
    while(!in.eof()){
        string s;
        in >> s;
        if(!s.empty())
            input.emplace_back(s);
    }
}

void Day3::solve() {
    // Part 1
    int sum = 0;

    // Separate
    auto backpacks = separate(input);
    // Get common
    for(auto& b : backpacks){
        auto commons = getCommon(b.left, b.right);
        // Get the priority
        auto priorities = getPriorities(commons);
        // Get the highest
        auto sorted = sortPriorities(priorities);
        // Get the value
        auto c = sorted[0];
        auto value = priorities[c];

        sum += value;

        cout << c << " : " << value << endl;
    }

    cout << "Parti 1 : " << sum << endl;

    // Part 2

    sum = 0;
    auto groups = getGroups(input);

    for(auto& group : groups){
        auto common = getCommon(group);
        auto value = getPriority(common);
        sum += value;

        cout << common << " : " << value << endl;
    }
    cout << "Partie 2 : " << sum << endl;

}

vector<Day3::Backpack> Day3::separate(const Input &in) {
    vector<Backpack> res;
    for(auto& i : in){
        auto n = i.size();
        res.push_back({
            i.substr(0, n/2),
            i.substr(n/2)
        });
    }
    return res;
}

set<char> Day3::getCommon(const string &a, const string &b) {
    set<char> passed;
    set<char> commons;

    for(auto& c : a){
        passed.insert(c);
    }
    for(auto& c : b){
        if(passed.find(c) != passed.end()){
            commons.insert(c);
        }
    }

    return commons;
}

map<char, int> Day3::getPriorities(const set<char> &b) {
    map<char, int> m;
    for(char c : b){
        m[c] = getPriority(c);
    }
    return m;
}

int Day3::getPriority(char c) {
    if(c >= 'a' && c <= 'z')
        return c-'a'+1;
    return c-'A'+26+1;
}

vector<char> Day3::sortPriorities(const map<char, int> &m) {
    vector<char> keys;
    for(auto& p : m){
        keys.emplace_back(p.first);
    }

    sort(keys.begin(), keys.end(), [&m](char a, char b){
        return m.at(a) > m.at(b);
    });

    return keys;
}

vector<vector<string>> Day3::getGroups(const Day3::Input &in) {
    vector<vector<string>> res;

    for(int i=0; i<in.size(); i+=3){
        res.push_back({
            in[i+0],
            in[i+1],
            in[i+2]
        });
    }

    return res;
}

char Day3::getCommon(const vector<string> &strs) {
    map<char, int> m;
    for(auto& str : strs){
        set<char> used;
        for(auto c : str){
            if(used.find(c) == used.end()) {
                used.insert(c);
                m[c]++;
            }
        }
    }

    for(auto& p : m){
        if(p.second == strs.size())
            return p.first;
    }
    throw runtime_error("Could not find a common char");
}
