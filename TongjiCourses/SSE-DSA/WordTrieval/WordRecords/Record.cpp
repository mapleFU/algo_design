//
// Created by 付旭炜 on 2017/10/3.
//

#include "Record.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Record &record) {
    os << std::string("line: ") << record.line << "   " << "position: " << record.position;
    return os;
}

void WordRecord::output_line_records(int line) {
    long lo = 0;
    long hi = word_record.size();
    while (hi - lo >= 1) {
        auto mid = (hi + lo) / 2;
        if (word_record[mid].line < line) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    auto index = lo;
    while (word_record[index].line == line) {
        std::cout << word_record[index++] << '\n';
    }
    if (index - lo > 0) {
        std::cout << "出现" << index - lo << "次" << std::endl;
    }
}

void WordRecord::show_all() const {
    int line = 0;
    for (int i = 0; i < word_record.size(); ++i) {
        if (word_record[i].line != line) {
            line = word_record[i].line;
            std::cout << "line " << line << ": \n";
        }
        std::cout << word_record[i] << '\n';
    }
}
