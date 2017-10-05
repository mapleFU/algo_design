//
// Created by 付旭炜 on 2017/10/5.
//

#ifndef WORDTRIEVAL_WORDTOKENIZER_H
#define WORDTRIEVAL_WORDTOKENIZER_H


#include <string>
#include "Record.h"
#include <sstream>
#include <set>



class WordTokenizer {
public:
    explicit WordTokenizer(const std::string&& _line): line(_line){
        cur_pos = 0;
    }
    explicit WordTokenizer(const std::string& _line): line(_line){
        cur_pos = 0;
    }
    bool get_word(Word& word);
    static std::set<char> alphabet;
    static bool in_alphabet(char ch);
private:
    const std::string line;
    int cur_pos;
};


#endif //WORDTRIEVAL_WORDTOKENIZER_H
