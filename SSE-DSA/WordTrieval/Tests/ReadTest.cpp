//
// Created by 付旭炜 on 2017/12/22.
//

#include "ReadTest.h"
#include <iostream>
#include <fstream>

#include "../WordRecords/WordRecords.h"
#include "../WordRecords/WordTokenizer.h"

void ReadTest::main() {
    std::string filename = "/Users/fuasahi/ClionProjects/WordTrieval/Testdata/11.txt";
    std::ifstream file_in(filename);

    std::string line;
    WordRecords records;
    for (int line_pos = 1; getline(file_in, line); ++line_pos) {
        WordTokenizer wordTokenizer(line);
        Word tmp_word;
        for (int pos = 1; wordTokenizer.get_word(tmp_word); ++pos) {
            records.add_record(tmp_word, line_pos, pos);
        }
    }

    records.show_all();
}
