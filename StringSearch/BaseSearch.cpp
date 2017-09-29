//
// Created by 付旭炜 on 2017/5/10.
//

#include "BaseSearch.h"

size_t BaseSearch::search(const std::string &pat) {
    for (size_t  i = 0; i < text.size() - pat.size(); ++i) {
        int j;
        for (j = 0; j < pat.size(); ++j) {
            if (text[i + j] != pat[j])
                break;
        }
        if (j == pat.size()) {

        }
    }
}
