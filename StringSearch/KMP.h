//
// Created by 付旭炜 on 2017/5/10.
//

#ifndef STRING_ALGO_KMP_H
#define STRING_ALGO_KMP_H


#include "BaseSearch.h"

class KMP: public BaseSearch {
public:
    KMP(const std::string& s): BaseSearch(s) {}
    size_t search(const std::string& pat) override ;
};


#endif //STRING_ALGO_KMP_H
