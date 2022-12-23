//
// Created by fgdou on 23/12/22.
//

// 2096
// 2211
// 2320

#include <iostream>
#include "Day16.h"
#include <algorithm>

void Day16::parse(std::istream &in) {
    Input i{};
    while(!in.eof()){
        string line;
        getline(in, line);

        if(line.empty())
            continue;

        string name = string(line, 6, 2);
        int rate;
        string destinations = string(line, line.find(' ', 45)+1);

        sscanf(line.c_str()+8, " has flow rate=%d;", &rate);

        i.flowrate[name] = rate;

        for(int j=0; j < destinations.size(); j+=4){
            i.tunnels[name].insert(string(destinations, j, 2));
        }
    }
    input = i;
}

void Day16::solve() {
    Model m(1000, .05, .05, input);

    int last = 0;
    for (int i = 0; i < 10000; ++i) {
        m.execute();
        int n = m.getMax();
        if(n != last){
            cout << i << ' ' << n << endl;
        }
        last = n;
    }
}

int Day16::countEdges(const map<string, set<string>> &tunnels) {
    int cnt = 0;
    for(auto& t : tunnels){
        cnt += t.second.size();
    }
    return cnt/2;
}

int Day16::Actions::evaluate(const Input &input) {
    if(count != -1)
        return count;


    if(actions.size() > MAX)
        return 0;

    int cnt = 0;
    int minutes = 30;
    string pos = START_POS;
    set<string> opened;

    for(auto& a : actions){
        minutes--;
        if(a.action == Element::MOVE){
            if(input.tunnels.at(pos).find(a.pos) == input.tunnels.at(pos).end())
                throw runtime_error("Error, path not available from " + pos + " to " + a.pos);
            pos = a.pos;
        }else{
            if(opened.find(pos) == opened.end()){
                cnt += minutes * input.flowrate.at(pos);
                opened.insert(pos);
            }
        }
    }

    count = cnt;

    return cnt;
}

Day16::Actions Day16::Actions::random(const Day16::Input &input, int minutes) {
    Actions a{};
    string pos = START_POS;

    Actions::fill(input, a, pos);

    return a;
}

Day16::Actions Day16::Actions::randomize(double p, const Input& input) const {
    Actions res{};
    string pos = START_POS;

    for(auto& a : actions){
        double r = (double)rand()/RAND_MAX;
        if(r > p) {
            // dont change
            res.actions.push_back(a);
            if(a.action == Element::MOVE) {
                pos = a.pos;
            }
        }else{
            // change
            if(r > p/2){
                // open / close
                if(a.action == Element::OPEN){
                    // close
                }else{
                    res.actions.push_back(Element{
                        "OPEN",
                        Element::OPEN
                    });
                    res.actions.push_back(a);
                    pos = a.pos;
                }
            }else{
                // other path
                break;
            }
        }
    }

    fill(input, res, pos);

    return res;
}

void Day16::Actions::fill(const Day16::Input &input, Day16::Actions &res, string &pos) {
    while(res.actions.size() < MAX){
        vector<string> possibilities(input.tunnels.at(pos).begin(), input.tunnels.at(pos).end());
        auto a = Element::random(possibilities);
        if(a.action == Element::MOVE)
            pos = a.pos;
        res.actions.push_back(a);
    }
}

Day16::Actions
Day16::Actions::generateChild(double mutation, const Day16::Input &inputs, const Day16::Actions &other) const {
    Actions res{};
    string pos = START_POS;

    for(auto& a : actions){
        double v = (double)rand()/RAND_MAX;

        if(v < mutation){
            for(auto& f : other.find(pos)){
                if(f.action == Element::MOVE)
                    pos = f.pos;
                res.actions.push_back(f);
            }
            break;
        }

        res.actions.push_back(a);
        if(a.action == Element::MOVE)
            pos = a.pos;
    }

    fill(inputs, res, pos);

    return res;
}

vector<Day16::Element> Day16::Actions::find(const string &pos) const {
    for(auto it = actions.begin(); it != actions.end(); it++){
        if(it->action == Element::MOVE && it->pos == pos){
            return {it+1, actions.end()};
        }
    }
    return {};
}


Day16::Element Day16::Element::random(const vector<string>& possibilities) {
    Element e {
        possibilities[rand()%possibilities.size()],
        ((rand()%2 == 0) ? MOVE : OPEN)
    };
    return e;
}

Day16::Model::Model(int population, double prob, double mutation, const Input& input)
    : mutation(mutation), prob(prob), input(input)
{
    for(int i=0; i<population; i++)
        this->population.push_back(Actions::random(input, MAX));
}

int Day16::Model::getMax() {
    int m = 0;
    for(auto& p : population){
        m = max(m, p.evaluate(input));
    }
    return m;
}

void Day16::Model::execute() {
    vector<Actions> newVec{};

    // add children
    int total = 0;
    for(auto& a : population)
        total += a.evaluate(input);

    for(int i=1; i<MAX; i++) {
        auto& e1 = getProb(total);
        auto& e2 = getProb(total);
        auto child = e1.generateChild(mutation, input, e2);
        child.evaluate(input);
        newVec.push_back(child);
    }

    // mutation
    for(auto& a : newVec) {
        a = a.randomize(prob, input);
        a.evaluate(input);
    }

    // select the first
    sort(population.begin(), population.end(), [&](Actions& a1, Actions& a2){
        return a1.evaluate(input) > a2.evaluate(input);
    });
    newVec.push_back(population[0]);

    population = newVec;
}

const Day16::Actions &Day16::Model::getProb(int total) {
    double v = (double) rand() / RAND_MAX;
    int n = v*total;

    int cnt = 0;
    for(auto& a : population){
        if(cnt >= n)
            return a;
        cnt += a.evaluate(input);
    }
    return population[population.size()-1];
}
