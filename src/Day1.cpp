#include "abstract.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Day1.h"

using namespace std;

void Day1::parse(std::istream &in) {
    input.clear();
    vector<int> actual;
    while(!in.eof()){
        string line;
        getline(in, line);
        if(line.empty()){
            input.emplace_back(actual);
            actual.clear();
        }else{
            actual.emplace_back(stoi(line));
        }
    }
    input.emplace_back(actual);
}
vector<int> total(const vector<vector<int>>& in){
    vector<int> total;
    for(auto& l : in){
        int n = 0;
        for(auto& e : l)
            n += e;
        total.emplace_back(n);
    }
    return total;
}

void Day1::solve() {
    auto list = total(input);
    sort(list.begin(), list.end(), [](auto& e1, auto& e2){
        return e1 > e2;
    });

    cout << "Part1 : " << list[0] << endl;

    int total = list[0] + list[1] + list[2];

    cout << "Part2 : " << total << endl;

}