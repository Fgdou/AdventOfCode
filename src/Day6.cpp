//
// Created by fgdou on 12/6/22.
//

#include <list>
#include <map>
#include <iostream>
#include "Day6.h"

void Day6::parse(std::istream &in) {
    input.clear();
    in >> input;
}

void Day6::solve() {
    auto first = getFirst(input);

    cout << "Parti 1 : " << first << endl;
}

int Day6::getFirst(const string& input) {
    map<char, int> m;

    for(int i=0; i<n; i++)
        m[input[i]]++;
    for(int i=n; i<input.size(); i++){
        m[input[i]]++;
        m[input[i-n]]--;

        if(!hasDouble(m))
            return i+1;
    }
    return -1;
}

bool Day6::hasDouble(const map<char, int> &m) {
    for(auto& p : m){
        if(p.second > 1)
            return true;
    }
    return false;
}
