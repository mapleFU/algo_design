//
// Created by 付旭炜 on 2018/1/13.
//

#ifndef POLYNO_COUNTERBUILDER_H
#define POLYNO_COUNTERBUILDER_H


#include "poly.h"

class CounterBuilder {
private:
    int bill_1;     //1元钞票
    int bill_2;     //2元钞票
    int bill_5;     //5元钞票

    poly    * poly1 = nullptr,
            * poly2 = nullptr,
            * poly5 = nullptr,
            * final_poly = nullptr;
public:
    CounterBuilder(int b1, int b2, int b5): bill_1(b1), bill_2(b2), bill_5(b5){}
    void count_all() {
        final_poly = new poly((*poly1) * (*poly2) * (*poly5));
    }

    ~CounterBuilder() {
        delete poly1;
        delete poly2;
        delete poly5;
        delete final_poly;
    }

    void run() {
        count_poly();
        count_all();
    }

    void print_all() const {
        std::cout << bill_1 << "张1元，"<< bill_2 <<"张两元" << bill_5 << "张五元\n:";
        std::cout << *final_poly << std::endl;
        for (const auto& pairs: final_poly->polyno) {
            if (pairs.expon == 0) {
                break;
            }
            std::cout << "组合成 " << pairs.expon << "的选项有" << pairs.coef << "种\n" ;
        }
        std::cout << "\n\n";
    }
private:
    void build_vector(std::vector<std::pair<int, int>>& to_build, int bill, int bill_num) {
         int base_bill = 0;
        for (int i = bill_num; i >= 0; --i) {
            // 1 + ...
            to_build.push_back(std::make_pair<int, int>(1, base_bill + i * bill));
        }
    }
    void count_poly() {


        std::vector<std::pair<int, int>> p1_vec;
        build_vector(p1_vec, 1, bill_1);
        poly1 = new poly(p1_vec);

        std::vector<std::pair<int, int>> p2_vec;
        build_vector(p2_vec, 2, bill_2);
        poly2 = new poly(p2_vec);

        std::vector<std::pair<int, int>> p5_vec;
        build_vector(p5_vec, 5, bill_5);
        poly5 = new poly(p5_vec);
    }

};


#endif //POLYNO_COUNTERBUILDER_H
