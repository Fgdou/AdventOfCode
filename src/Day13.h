//
// Created by fgdou on 12/14/22.
//

#ifndef ADVENTOFCODE2022_DAY13_H
#define ADVENTOFCODE2022_DAY13_H


#include <memory>
#include <vector>
#include "abstract.h"

// 0h00
// 1h23

using namespace std;
class Day13 : public Abstract {
private:

    class Element {
    public:
        enum class Type {
            Value,
            List
        };
        enum class Order {
            GOOD,
            BAD,
            CONTINUE
        };

        static shared_ptr<Day13::Element> parse(const string &str, int &start);
        static shared_ptr<Element> divider(int n);

        virtual Type getType() const = 0;
        virtual Order checkOrder(const Element &other) const = 0;
        virtual const Element & get(int n) const = 0;
        virtual int count() const = 0;

        virtual bool equal(const Element& other) const = 0;

        virtual void print() const = 0;

        static int getFirstChar(const string& s, int start);
    };
    class Value : public Element {
    private:
        int n;
    public:
        explicit Value(int n);
        Value(const string &s, int& start);

        Type getType() const override;

        Order checkOrder(const Element &other) const override;

        const Element & get(int n) const override;

        bool equal(const Element &other) const override;

        int count() const override;

        void print() const override;
    };
    class List : public Element {
    private:
        vector<shared_ptr<Element>> list;
    public:
        void addElement(shared_ptr<Element>& e);
        List(const string& n, int& start);
        List() = default;

        Type getType() const override;

        bool equal(const Element &other) const override;

        int count() const override;

        Order checkOrder(const Element &other) const override;

        const Element &get(int n) const override;

        void print() const override;
    };

    vector<shared_ptr<Element>> input;

public:
    void parse(istream &in) override;

    void solve() override;
};


#endif //ADVENTOFCODE2022_DAY13_H
