//
// Created by 付旭炜 on 2017/10/3.
//

#ifndef WORDTRIEVAL_RECORD_H
#define WORDTRIEVAL_RECORD_H

#include <string>
#include <vector>

/*
 * Word represents string
 */
using Word = std::string;

class Record {
public:
    friend class WordRecord;
    friend std::ostream&operator<<(std::ostream& os, const Record& record);
    Record(int iline, int iposition): line(iline), position(iposition){}
private:
    int line;       //行号
    int position;   //位置
};

/*
 * A WORDS RECORD
 */
class WordRecord {
private:
    // DATAS
    std::vector<Record> word_record;
public:
    void output_line_records(int line);
    /*
     * 加入必定有序的记录
     */
    void push_back_record(const Record& record) {word_record.push_back(record);}
    int counts() { return word_record.size();}
    void show_all();
};



#endif //WORDTRIEVAL_RECORD_H
