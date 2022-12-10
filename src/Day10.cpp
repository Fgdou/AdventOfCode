//
// Created by fgdou on 12/10/22.
//

#include "Day10.h"
#include <algorithm>
#include <iostream>

void Day10::parse(istream &in) {
    input.clear();
    while(!in.eof()){
        string name;
        int n;

        in >> name;
        if(name == "noop")
            input.emplace_back(make_shared<Noop>());
        else{
            in >> n;
            input.emplace_back(make_shared<Add>(n, name[name.size()-1]));
        }
    }
}

void Day10::solve() {
    map<char, int> registers;
    registers['x'] = 1;

    int ncycles = 0;

    int result = 0;

    vector<char> CRT;

    for(auto& c : input){
        while(!c->done()){
            int pos = registers['x'];
            if(ncycles%40 >= (pos%40-1) && ncycles%40 <= (pos%40+1))
                CRT.emplace_back('#');
            else
                CRT.emplace_back('.');

            ncycles++;
            if(std::find(cycles.begin(), cycles.end(),ncycles) != cycles.end()){
                result += ncycles*registers['x'];
            }
            c->execute(registers);
        }
    }

    cout << "Part 1 : " << result << endl;
    cout << "Part 2 : " << endl;
    printCRT(CRT);
}

void Day10::printCRT(const vector<char> &crt) {
    for(int i=0; i<crt.size(); i++){
        cout << crt[i];
        if(i%40 == 39)
            cout << '\n';
    }
    cout << '\n' << endl;
}

void Day10::Noop::execute(map<char, int> &registers) {
    d = true;
}

bool Day10::Noop::done() {
    return d;
}

void Day10::Add::execute(map<char, int> &registers) {
    if(ncycles == 1){
        registers[c] += n;
    }
    ncycles--;
}

Day10::Add::Add(int n, char c) : n(n), c(c) {}

bool Day10::Add::done() {
    return ncycles == 0;
}
