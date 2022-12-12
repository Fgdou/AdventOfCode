//
// Created by fgdou on 12/12/22.
//

#ifndef ADVENTOFCODE2022_UTILS_H
#define ADVENTOFCODE2022_UTILS_H

#include <iosfwd>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v){
    for(auto& vv : v) {
        for(auto& vvv : vv)
            cout << vvv << ' ';
        os << "\n";
    }
    return os;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v){
    for(auto& vv : v)
        os << vv << '\n';
    return os;
}
#endif //ADVENTOFCODE2022_UTILS_H
