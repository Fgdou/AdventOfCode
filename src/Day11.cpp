//
// Created by fgdou on 12/11/22.
//

#include <sstream>
#include "Day11.h"
#include <algorithm>
#include <iostream>

void Day11::parse(istream &in) {
    input.clear();

    while(!in.eof()){
        Monkey monkey{};

        string line;
        getline(in, line);

        // Items
        getline(in, line);
        string list = string(line, 18);

        for (int i = 0; i < list.size(); ++i)
            if(list[i] == ',')
                list[i] = ' ';

        istringstream ss(list);
        while(!ss.eof()){
            int n;
            ss >> n;
            monkey.items.emplace_back(n);
        }

        // Operation
        getline(in, line);
        string last(line, 26);

        monkey.operationNumber = -1;
        if(last == "old")
            sscanf(line.c_str(), "  Operation: new = old %c", &monkey.operation);
        else
            sscanf(line.c_str(), "  Operation: new = old %c %ld", &monkey.operation, &monkey.operationNumber);

        // Condition
        getline(in, line);
        sscanf(line.c_str(), "  Test: divisible by %d", &monkey.condition);
        getline(in, line);
        sscanf(line.c_str(), "    If true: throw to monkey %d", &monkey.monkeyTrue);
        getline(in, line);
        sscanf(line.c_str(), "    If false: throw to monkey %d", &monkey.monkeyFalse);

        // Last line
        if(!in.eof())
            getline(in, line);

        input.emplace_back(monkey);
    }
}

void Day11::solve() {
    printAll(input, 0);
    for (int i = 0; i < 20; ++i){
        round(input);
        printAll(input, i+1);
    }

    auto count = countItems(input);

    long part1 = ((long)count[0])*count[1];
    cout << "Part 1 : " << part1 << endl;
}

void Day11::round(vector<Monkey> &monkeys) {
    for(auto& m : monkeys){
        m.moveItems(monkeys);
    }
}

vector<int> Day11::countItems(const vector<Monkey> &monkeys) {
    vector<int> res;

    for(auto& m : monkeys)
        res.emplace_back(m.getCountItems());

    std::sort(res.begin(), res.end(), [](auto a, auto b){
        return a > b;
    });

    return res;
}

void Day11::printAll(const vector<Monkey> &monkeys, int round) {
    cout << "Round " << round << endl;
    for (int i = 0; i < monkeys.size(); ++i)
        monkeys[i].print(i);
    cout << endl;
}

void Day11::Monkey::moveItems(vector<Monkey> &monkeys) {
    for(auto& item : items){
        calcOperation(item);
        item.div(3);
        int pos = check(item);
        monkeys[pos].items.emplace_back(item);
        countItems++;
    }
    items.clear();
}

int Day11::Monkey::check(const Item &item) const {
    if(item.modulus(condition))
        return monkeyTrue;
    return monkeyFalse;
}

void Day11::Monkey::calcOperation(Item &item) const {
    auto n = Item(operationNumber);

    if(operationNumber == -1)
        n = item;

    if(operation == '*')
        return item.mul(n);
    return item.add(n);
}

int Day11::Monkey::getCountItems() const {
    return countItems;
}

void Day11::Monkey::print(int n) const {
    cout << n << ": ";
    for(auto& i : items)
        cout << i.getValue() << ", ";
    cout << endl;
}

Day11::Item::Item(long n): value(n){}

void Day11::Item::add(const Item &n) {
    value += n.getValue();
}

void Day11::Item::mul(const Item &n) {
    value *= n.getValue();
}

long Day11::Item::getValue() const {
    return value;
}

bool Day11::Item::modulus(int n) const {
    return value % n == 0;
}

void Day11::Item::div(int n) {
    value /= n;
}
