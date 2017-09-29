//
// Created by 付旭炜 on 2017/5/10.
//

#ifndef STRING_ALGO_BASESEARCH_H
#define STRING_ALGO_BASESEARCH_H

#include <string>

class BaseSearch {
public:
    BaseSearch(const std::string &s): text(s) {}
    BaseSearch() = delete;
    virtual size_t search(const std::string& pat);
private:
    const std::string text;
    // 预处理
    virtual void pre_proc() {}
};


#endif //STRING_ALGO_BASESEARCH_H
