//
// Created by 付旭炜 on 2017/5/10.
//

#ifndef STRING_ALGO_BM_H
#define STRING_ALGO_BM_H


#include <string>
#include "BaseSearch.h"

class BM: public BaseSearch {
public:
    BM(const std::string &s): BaseSearch(s) {}
    size_t search(const std::string& pat);
private:
    constexpr static int _TABLE_SIZE = 26;
    std::string text;
    void pre_proc() override;
    size_t right();
    size_t _right[_TABLE_SIZE];
};


#endif //STRING_ALGO_BM_H
