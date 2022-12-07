//
// Created by fgdou on 12/7/22.
//

#include <stack>
#include <iostream>
#include <sstream>
#include "Day7.h"

void Day7::parse(std::istream &in) {
    input = make_shared<Dir>();
    stack<shared_ptr<Dir>> dirs;
    dirs.push(input);

    while(!in.eof()){
        string line;
        getline(in, line);

        if(line[0] == '$'){
            if(line[2] == 'c'){
                string name = string(line, 5);
                if(name == "/"){
                    while(dirs.size() > 1)
                        dirs.pop();
                }else if(name == "..") {
                    dirs.pop();
                }else{
                    auto d = make_shared<Dir>();
                    dirs.top()->addDir(name, d);
                    dirs.push(d);
                }
            }
        }else{
            if(line[0] != 'd'){
                istringstream is(line);
                int size;
                string name;
                is >> size >> name;

                dirs.top()->addFile(name, size);
            }
        }
    }
}

void Day7::solve() {
    input->print(cout);
    cout << "Part 1 : " << input->countMoreThan(100000) << endl;

    int total = input->getSize();
    int toFree = 30000000 - (70000000-total);

    cout << "Part 1 : " << input->free(toFree) << endl;
}

void Day7::Dir::addFile(const string &s, int size) {
    files[s] = size;
}

Day7::Dir &Day7::Dir::getDir(const string &s) {
    if(dirs.find(s) == dirs.end())
        throw runtime_error("Dir " + s + " not found");
    return *dirs[s];
}

ostream& Day7::Dir::print(ostream &os, const string &depth) {
    for(auto& item : dirs){
        string depthP = depth + '\t';
        cout << depth << item.second->getSize() << ' ' << item.first << endl;
        item.second->print(os, depthP);
    }
    for (auto &item: files){
        cout << depth << item.second << ' ' << item.first << endl;
    }
    return os;
}

void Day7::Dir::addDir(const string& s, shared_ptr<Dir>& ptr) {
    dirs[s] = ptr;
}

int Day7::Dir::getSize() {
    if(size != -1)
        return size;
    size = 0;
    for(auto& i : files)
        size += i.second;
    for(auto& i : dirs)
        size += i.second->getSize();
    return size;
}

int Day7::Dir::countMoreThan(int n, bool first) {
    int sum = getSize();
    if(first || sum > n)
        sum = 0;
    for(auto& i : dirs){
        sum += i.second->countMoreThan(n, false);
    }
    return sum;
}

int Day7::Dir::free(int size) {
    int s = getSize();
    if(s < size)
        return 0;
    for(auto& i : dirs){
        int ss = i.second->free(size);
        if(ss != 0 && ss < s)
            s = ss;
    }
    return s;
}