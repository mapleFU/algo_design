//
// Created by 付旭炜 on 2017/3/5.
//

#ifndef POLYNO_POLY_H
#define POLYNO_POLY_H

#include <list>
#include <iostream>
#include <cmath>

struct polyData {
    int expon;
    int coef;
    polyData() = default;
    polyData(const int co, const int exp): expon(exp), coef(co) {}
    polyData(const polyData& data): expon(data.expon), coef(data.coef) {}
    polyData(const polyData&& data): expon(std::move(data.expon)), coef(std::move(data.coef)) {}
    polyData& operator=(const polyData& pd) {
        expon = pd.expon;
        coef = pd.coef;
        return *this;
    }
    void init() {this->expon = this->coef = 0;}     //初始化
};

class poly {
    friend std::ostream& operator<<(std::ostream &os, const poly &poly0);
//    friend std::ostream& operator<<(std::ostream &os, poly &&poly0);
private:
    std::list<polyData> polyno;
public:         //可以设计 operator = 减少重用；
    poly operator+(const poly&);
    poly& operator-(const poly&);
    poly& operator+=(const poly&);
    poly operator*(const poly&);
    poly& operator*=(const poly&);
    poly operator^(int n);
//    poly& operator=(poly&);
    poly& operator=(const poly&&);
//    poly& operator^=(poly&);
//    std::ostream& operator<<(std::ostream&, poly&);
    poly() = default;
    poly(const polyData& data): polyno{data} {}
//    poly(polyData&& data): polyno{std::move(data)} {}
    poly(const std::string&);
    poly(const poly& poly1): polyno(poly1.polyno) {}
    poly(const poly&& poly1): polyno(std::move(poly1.polyno)) {}
    void get_a_node(int coef, int expon);
};

inline int getNumber(unsigned long &pos, const std::string& str) {
    using namespace std;
    static const string numbers = "0123456789";
//    auto posEnd = str.find_first_not_of(numbers, pos);
    unsigned long posEnd;
    int ret = stoi(str.substr(pos), &posEnd, 10);
    pos += posEnd;
    return ret;
}
#endif //POLYNO_POLY_H
