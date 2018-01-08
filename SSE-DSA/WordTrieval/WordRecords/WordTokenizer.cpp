//
// Created by 付旭炜 on 2017/10/5.
//

#include "WordTokenizer.h"
#include <cctype>

std::set<char> WordTokenizer::alphabet{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                                  'Q','R','S', 'T','U','V','W','X','Y','Z','a','b','c','d','e','f',
                                  'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u',
                                  'v','w','x','y','z'};


bool WordTokenizer::in_alphabet(char ch) {
    return (alphabet.find(ch) != alphabet.end());
}

bool WordTokenizer::get_word(Word &word) {
    // do with pre
    word.clear();
    int pre = cur_pos;
    while (pre < line.size() && !in_alphabet(line[pre])) ++pre;

    if (pre == line.size()) {
        // 本行不再有正常的单词信息
        return false;
    } else {
        // 出现的PRE位置是首个字母
        word.push_back(std::tolower(line[pre]));
    }

    // 加入剩下的单词
    int cur = pre + 1;
    while (cur < line.size() && in_alphabet(line[cur])) {
        word.push_back(std::tolower(line[cur]));
        ++cur;
    }
    cur_pos = cur;

    // 一个字非a的单词是不正常的，继续读取
    if (word.size() == 1 && word != "a") {
        return get_word(word);
    }
    return true;
}


