#include <iostream>
#include <fstream>
#include <sstream>
#include "WordRecords/WordRecords.h"
#include "WordRecords/WordTokenizer.h"

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#include "Tests/ReadTest.h"
#include "Tests/SearchTest.h"
#endif

using namespace std;

int main() {
#ifdef DEBUG
    SearchTest::main();
#endif
    std::string filename;
    cout << "Please input the name of the text" << '\n';
    std::cin >> filename;

    // create file
    ifstream file_in(filename);

    std::string line;
    WordRecords records;

    for (int line_pos = 1; getline(file_in, line); ++line_pos) {
        WordTokenizer wordTokenizer(line);
        Word tmp_word;
        for (int pos = 1; wordTokenizer.get_word(tmp_word); ++pos) {
            records.add_record(tmp_word, line_pos, pos);
        }
    }
//
    // trieval
    Word search;
    while (true) {
        cout << "请输入你要检索的单词" << '\n';
        cin >> search;
        records.show_word(search);
    }
    return 0;
}