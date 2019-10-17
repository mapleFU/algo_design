//
// Created by 付旭炜 on 2017/3/5.
//

#include "poly.h"

poly poly::operator+(const poly &p2) {
//    auto retPoly(*this);
    poly retPoly = *this;
    for (auto& node: p2.polyno) {
        retPoly.get_a_node(node.coef, node.expon);
    }
    return retPoly;
}

poly &poly::operator+=(const poly &p2) {
    for (auto& node: p2.polyno) {
        this->get_a_node(node.coef, node.expon);
    }
    return *this;
}

poly poly::operator*(const poly &p2) {
    auto nodes2 = p2.polyno;
    poly thispoly;
    while (nodes2.size()) {
        polyData &node = nodes2.front();
        for (auto &nd: this->polyno) {
            int coef = nd.coef * node.coef;
            int exp = nd.expon + node.expon;
//            printf("coef:%d expon:%d\t", coef, exp);
            thispoly.get_a_node(coef, exp);
//            std::cout<<"test: "<<thispoly<<std::endl;
        }
        nodes2.pop_front();
    }
    return thispoly;
}

poly poly::operator^(int n) {
    poly retPoly("1");
    poly cntPoly = *this;
    while (n) {
        if (n % 2 == 1)
            retPoly *= cntPoly;
        cntPoly = cntPoly * cntPoly;
        n /= 2;
    }
    return retPoly;
}

poly::poly(const std::vector<std::pair<int, int>>& args) {
    for (const auto& pairs: args) {
        this->get_a_node(pairs.first, pairs.second);
    }
}

poly::poly(const std::string &str) {
    using std::string;
    //construct
    bool isadd(true);
    for (decltype(str.size()) i = 0; i < str.size(); i++) {
        if (str[i] == '+' || str[i] == '-') {
            isadd = (str[i] == '+') ? true: false;
        }
        if (isdigit(str[i])) {
            int val1 = getNumber(i, str);   //得到第一个值, i指向最后一个是数字的值
            int val2(0);
            val1 = isadd ? val1: -val1;
            isadd = true;
            if (i == str.size() || str[i] != 'x') {
//                polyno.emplace_back(val1, val2);
                this->get_a_node(val1, val2);
                i--;
            }
            else if (str.find("x^", i) == i) {
                i += 2;
                val2 = getNumber(i, str);
//                polyno.emplace_back(val1, val2);
                this->get_a_node(val1, val2);
                i--;
            }
            else if (str[i] == 'x') {   //只有一个x
                val2 = 1;
//                polyno.emplace_back(val1, val2);
                this->get_a_node(val1, val2);
                i += 1;
            }
        }
    }
}


std::ostream& operator<<(std::ostream &os, const poly &poly0) {
    bool start(true);
    for (auto ch: poly0.polyno) {
        if (start) {
            start = false;
            if (ch.coef < 0)
                os<<'-';
        }
        else
            os<<((ch.coef > 0)? '+':'-');

        os<<abs(ch.coef);
        if (ch.expon == 0)
            continue;
        else if (ch.expon != 1)
            os<<"x^"<<ch.expon;
        else
            os<<'x';
    }
    return os;
}

void poly::get_a_node(int coef, int expon) {
    polyData pD(coef, expon);
//    polyno.push_front(polyData(INT_MAX, INT_MAX));
    bool get(false);
    for (auto it = polyno.begin(); it != polyno.end(); it++) {
        if ((*it).expon > pD.expon)
            continue;
        else if ((*it).expon == pD.expon) {
            get = true;
            (*it).coef += pD.coef;
            if ((*it).coef == 0) {
                polyno.erase(it);
            }
            break;
        }
        else {
            polyno.insert(it, pD);
            get = true;
            break;
        }
    }
    if (!get) {
        polyno.push_back(pD);
    }
}

poly &poly::operator-(const poly &p2) {
    for (auto& node: p2.polyno) {
        this->get_a_node(-node.coef, node.expon);
    }
    return *this;
}

//poly &poly::operator=(poly &p2) {
//    this->polyno = p2.polyno;
//    return *this;
//}

poly &poly::operator=(const poly &&p2) {
    this->polyno = std::move(p2).polyno;
    return *this;
}

poly &poly::operator*=(const poly &p2) {
    *this = *this * p2;
    return *this;
}




