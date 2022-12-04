//
// Created by fgdou on 12/4/22.
//

#include <iostream>
#include "Day4.h"

void Day4::parse(std::istream &in) {
    input.clear();
    while(!in.eof()){
        string line;
        getline(in, line);
        if(line.empty())
            continue;

        Pair p{};

        sscanf(line.c_str(), "%d-%d,%d-%d",
            &p.first.left,
            &p.first.right,
            &p.second.left,
            &p.second.right
        );

        input.push_back(p);
    }
}

void Day4::solve() {
    int nContains = 0;
    int nOverlap = 0;
    for(auto& p : input){
        if(p.containsEachOther())
            nContains++;
        if(p.overlap())
            nOverlap++;
    }
    cout << "Part 1 : " << nContains << endl;
    cout << "Part 2 : " << nOverlap << endl;
}

bool Day4::Range::contains(const Day4::Range &other) const {
    return other.left >= left && other.right <= right;
}

bool Day4::Range::overlap(const Range& other) const{
    return !(left > other.right || right < other.left);
}

bool Day4::Pair::containsEachOther() const {
    return first.contains(second) || second.contains(first);
}

bool Day4::Pair::overlap() const {
    return first.overlap(second);
}
