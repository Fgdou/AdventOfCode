//
// Created by fgdou on 12/8/22.
//

#include <iostream>
#include "Day8.h"

void Day8::parse(std::istream &in) {
    input.clear();
    while(!in.eof()){
        string line;
        in >> line;
        vector<int> l;
        if(!line.empty()){
            for(char c : line){
                l.emplace_back(c-'0');
            }
            input.emplace_back(l);
        }
    }
}

void Day8::solve() {
    Visible v;
    for(auto & i : input){
        v.emplace_back(i.size());
    }

    for(int x=0; x<input[0].size(); x++){
        check(x, 0, 0, 1, input, v);
        check(x, input.size()-1, 0, -1, input, v);
    }
    for(int y=0; y<input.size(); y++){
        check(0, y, 1, 0, input, v);
        check(input[0].size()-1, y, -1, 0, input, v);
    }

    int n = count(v);

    print(v);
    cout << "Part 1 : " << n << endl;

    int max = 0;
    for(int y=0; y<input.size(); y++){
        for(int x=0; x<input[0].size(); x++){
            int cnt = 1;
            int v = input[y][x];

            cnt *= check(x+1, y,  1,  0, input, v);
            cnt *= check(x-1, y, -1,  0, input, v);
            cnt *= check(x, y+1,  0,  1, input, v);
            cnt *= check(x, y-1,  0, -1, input, v);

            if(cnt > max)
                max = cnt;
        }
    }

    cout << "Part 2 : " << max << endl;
}

void Day8::print(const Day8::Visible &v) {
    for(auto& vec : v){
        for(bool value : vec){
            cout << ((value) ? 'X' : '.');
        }
        cout << endl;
    }
}

bool Day8::isValid(int x, int y, const Input &input) {
    return x >= 0 && y >= 0 && x < input[0].size() && y < input.size();
}

void Day8::check(int x, int y, int dx, int dy, const Day8::Input &in, Day8::Visible &visible) {
    int v = -1;
    while(isValid(x, y, in)){
        int height = in[y][x];

        if(height > v){
            visible[y][x] = true;
            v = height;
        }

        x += dx;
        y += dy;
    }
}
int Day8::check(int x, int y, int dx, int dy, const Day8::Input &in, int base) {
    int cnt = 0;
    while(isValid(x, y, in)){
        int height = in[y][x];

        cnt++;

        if(height >= base)
            break;

        x += dx;
        y += dy;
    }
    return cnt;
}

int Day8::count(const Day8::Visible &v) {
    int n = 0;
    for(auto& l : v){
        for(bool b : l){
            if(b)
                n++;
        }
    }
    return n;
}
