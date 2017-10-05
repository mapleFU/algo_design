//
// Created by 付旭炜 on 2017/10/3.
//

#include "WordRecords.h"
#include <iostream>

int WordRecords::count_times(const Word &word) {
    auto iter = record_map.find(word);
    if (iter != record_map.end()) {
        return iter->second.counts();
    }
    return 0;
}

void WordRecords::show_word(const Word &word) {
    const auto iter = record_map.find(word);
    if (iter != record_map.end()) {
        return iter->second.show_all();
    }
    std::cout << "There is no word \"" << word << "\"\n";
}
