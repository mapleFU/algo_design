//
// Created by 付旭炜 on 2017/10/3.
//

#ifndef WORDTRIEVAL_WORDRECORD_H
#define WORDTRIEVAL_WORDRECORD_H

#include "Record.h"
#include <vector>
#include <map>
#include <iostream>

struct wordcomp {
    bool operator() (const Word& word1, const Word& word2) const {
        return word1 < word2;
    }
};

class WordRecords {
private:
    std::map<Word, WordRecord, wordcomp> record_map;
public:
    void add_record(const Word& word, int line, int position) {
        auto iter = record_map.find(word);
        if (iter == record_map.end()) {
            // didn't find it
            record_map[word] = WordRecord();
            record_map[word].push_back_record(Record(line, position));
        } else {
            iter->second.push_back_record(Record(line, position));
        }
    }
    /*
     * @word: 输入要判定次数的单词
     * @return: 次数
     */
    int count_times(const Word& word);
    void show_word(const Word& word);
    /*
     * 在测试的时候展现所有的数据
     */
    void show_all();
};



#endif //WORDTRIEVAL_WORDRECORD_H
