# n皇后模拟系统

## 设计
### 类设计
#### QueenTable
存储八皇后的类
```
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
```

##### public成员函数
1.
`void show_table(std::ostream& os)`向指定的输出流打印八皇后

2.
`int dfs(int depth = 1, bool is_print = false, std::ostream& os=std::cout)`

用深度优先搜索搜索出八皇后的结果, 参数介绍如下
```
depth: 目前搜索的深度
is_print: 指定是否需要打印(如果是TRUE会打印八皇后所有搜索结果)
std::ostream& os: 需要打印(is_print = true)时指定的输出流， 默认为std::cout
```

##### private成员
`int judge_queen(int range)`

判断在搜索的深度(`range`)中时候满足N皇后的条件。不满足返回0。

`std::vector<int> _table`N皇后实际被存储的地方, `_table[i] = j`表示八皇后第i+1 行 第 J列有皇后。

#### NQueen
实际驱动八皇后的类

```
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
```

##### 公有接口
```doxygen
    void run(bool is_print=false);
```
运行八皇后, is_print字段表示是否显示。重复运行不会被重复操作。

```
 int get_results();
```
run()运行后后返回结构，否则会进行RUN()操作。

##### 私有接口和字段

`QueenTable _table;`

保存的QueenTable

`bool _runned = false;`
 
八皇后是否已经运行，默认为FALSE

`int _result;`

八皇后总运算的结果

## 实现
### 整体系统的实现
main.cpp
```doxygen
#include <iostream>

#include "NQueen.h"

using namespace std;

int main() {
    int n ;
    cout << "现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上"<<'\n' << "请输入皇后的个数\n";
    cin >> n;
    NQueen queen(n);
    
    queen.run(true);
    cout << queen.get_results() << endl;
    
    return 0;
}
```

主程序根据输入N创建NQueen对象，使NQueen对象调用RUN(), 并用get_result()获取最终结果并打印。

以下为示例(run()参数为true)
```doxygen
现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上
请输入皇后的个数
>>> 3
0
```

```doxygen
现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上
请输入皇后的个数
>>> 4
O X O O 
O O O X 
X O O O 
O O X O 

O O X O 
X O O O 
O O O X 
O X O O 

2
```

run()参数为false(不打印八皇后信息)
```doxygen
现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上
请输入皇后的个数
>>> 7
40
```

```doxygen
现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上
请输入皇后的个数
>>> 12
14200
```

### 八皇后计算逻辑
计算八皇后的主要函数是QueenTable.dfs, 下面是其介绍
```doxygen
int QueenTable::dfs(int depth, bool is_print, std::ostream& os) {
    int sum = 0;
    for (int j = 1; j <= _table.size(); ++j) {
        _table[depth] = j;

        if (judge_queen(depth + 1)) {
            if (depth + 1 == _table.size()) {
                if (is_print) {
                    show_table(os);
                }
                return 1;
            } else {
                sum += dfs(depth + 1, is_print, os);
            }
        }
    }
    _table[depth] = 0;
    return sum;
}
```
DFS函数给进入的层赋值，并对新赋给的值用`judge_queen`函数检验。
他的返回值是之前赋值不变的可能总值。

```
int QueenTable::judge_queen(int range) {
//    std::cout << "Judge:\n";
//    show_table(std::cout);
    int i = range - 1;
    for (int k = 0; k < i; ++k) {
        if (abs(i - k) == abs(_table[i] - _table[k]) || _table[i] == _table[k])
            return false;
    }
    return true;
}
```
由于判断是逐层深入的，所以每次只要对新的一层结果进行判断即可。

