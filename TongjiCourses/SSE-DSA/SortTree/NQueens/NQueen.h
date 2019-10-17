//
// Created by 付旭炜 on 2017/11/15.
//

#ifndef NQUEENS_NQUEEN_H
#define NQUEENS_NQUEEN_H

#include <vector>
#include <iostream>

class QueenTable {
private:
    // 实际存储
    std::vector<int> _table;
    int judge_queen(int range);
public:
    friend class NQueen;
    /*
     * 向输出流os打印八皇后表
     */
    void show_table(std::ostream& os);
    explicit QueenTable(size_t n): _table(n) {}
    int dfs(int depth = 1, bool is_print = false, std::ostream& os=std::cout);
};

class NQueen {
private:
    QueenTable _table;
    bool _runned = false;    //是否运行
    int _result;
public:
    /*
     * 构造函数
     */
    explicit NQueen(size_t n): _table(n) {}
    // construct by is
//    explicit NQueen(std::istream& is);

    // 操作接口

    /*
     * 运行八皇后, is_print字段表示是否显示
     */
    void run(bool is_print=false);
    /*
     * 运行后返回结构，否则抛出错误
     */
    int get_results();
};



#endif //NQUEENS_NQUEEN_H
