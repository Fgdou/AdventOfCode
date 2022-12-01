#pragma once
#include <istream>

class Abstract {
public:
    Abstract() = default;
    virtual ~Abstract() = default;

    virtual void parse(std::istream& in) = 0;
    virtual void solve() = 0;
};