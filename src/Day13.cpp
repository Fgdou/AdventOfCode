//
// Created by fgdou on 12/14/22.
//

#include <iostream>
#include <cassert>
#include "Day13.h"
#include <algorithm>

void Day13::parse(istream &in) {
    input.clear();

    while(!in.eof()){
        string line;
        getline(in, line);

        if(line.empty())
            continue;

        int start = 0;
        input.push_back(Element::parse(line, start));
    }
}

void Day13::solve() {

    // Part 1
    int sumIndices = 0;
    for(int i=0; i<input.size()/2; i++){
        auto& p1 = input[i*2];
        auto& p2 = input[i*2+1];

        if(p1->checkOrder(*p2) == Element::Order::GOOD){
            sumIndices += i+1;
        }
    }

    cout << "Part 1 : " << sumIndices << endl;

    // Part 2
    auto d1 = Element::divider(2);
    auto d2 = Element::divider(6);

    input.push_back(d1);
    input.push_back(d2);

    // Sort
    sort(input.begin(), input.end(), [](auto& a, auto& b){
        return a->checkOrder(*b) == Element::Order::GOOD;
    });

    // Find
    int i1 = std::find(input.begin(), input.end(), d1) - input.begin() +1;
    int i2 = std::find(input.begin(), input.end(), d2) - input.begin() +1;

    int key = i1*i2;
    cout << "Part 2 : " << key << endl;
}

Day13::Element::Type Day13::List::getType() const {
    return Type::List;
}

Day13::Element::Order Day13::List::checkOrder(const Element &other) const {
    int m = min(count(), other.count());
    for(int i=0; i<m; i++){
        auto res = get(i).checkOrder(other.get(i));
        if(res == Element::Order::GOOD || res == Element::Order::BAD)
            return res;
    }
    if(count() < other.count())
        return Element::Order::GOOD;
    if(count() > other.count())
        return Element::Order::BAD;
    return Element::Order::CONTINUE;
}
void Day13::List::addElement(shared_ptr<Element> &e) {
    list.push_back(e);
}

void Day13::List::print() const {
    cout << '[';
    for(auto& v : list){
        v->print();
        cout << ',';
    }
    cout << ']';
}

Day13::List::List(const string& s, int &start) {
    assert(s[start] == '[');
    start++;
    while(s[start] != ']'){
        list.push_back(Element::parse(s, start));
        if(s[start] == ',')
            start++;
    }
    start++;
}

const Day13::Element &Day13::List::get(int n) const {
    return *list[n];
}

int Day13::List::count() const {
    return list.size();
}

bool Day13::List::equal(const Day13::Element &other) const {
    if(count() != other.count())
        return false;
    for (int i = 0; i < count(); ++i){
        if(!get(i).equal(other.get(i)))
            return false;
    }
    return true;
}

Day13::Element::Type Day13::Value::getType() const {
    return Type::Value;
}

Day13::Element::Order Day13::Value::checkOrder(const Element &other) const {
    if(other.getType() == Element::Type::Value){
        if(n < ((const Value&) other).n)
            return Element::Order::GOOD;
        if(n > ((const Value&) other).n)
            return Element::Order::BAD;
        return Element::Order::CONTINUE;
    }else{
        List l;
        shared_ptr<Element> ptr = make_shared<Value>(n);
        l.addElement(ptr);
        return l.checkOrder(other);
    }
}

Day13::Value::Value(int n)
    : n(n)
{

}

void Day13::Value::print() const {
    cout << n;
}

Day13::Value::Value(const string &s, int &start) {
    int pos = getFirstChar(s, start);

    auto valueString = string(s, start, pos);

    n = stoi(valueString);

    start += pos-start;
}

const Day13::Element & Day13::Value::get(int n) const {
    return *this;
}

int Day13::Value::count() const {
    return 1;
}

bool Day13::Value::equal(const Day13::Element &other) const {
    return(other.getType() == Element::Type::Value && n == ((const Value&) other).n);
}

shared_ptr<Day13::Element> Day13::Element::parse(const string &str, int &start) {
    assert(start < str.size());
    char c = str[start];

    if(c == '[')
        return make_shared<List>(str, start);
    return make_shared<Value>(str, start);
}

int Day13::Element::getFirstChar(const string &s, int start) {
    int pos1 = s.find(',', start);
    int pos2 = s.find(']', start);

    if(pos1 == -1)
        return pos1 = pos2;
    assert(pos1 != -1);

    return min(pos1,pos2);
}

shared_ptr<Day13::List::Element> Day13::Element::divider(int n) {
    auto p1 = make_shared<List>();
    auto p2 = make_shared<List>();
    auto v = make_shared<Value>(n);

    shared_ptr<Element> e3 = v;
    shared_ptr<Element> e2 = p2;

    p1->addElement(e2);
    p2->addElement(e3);

    return p1;
}
