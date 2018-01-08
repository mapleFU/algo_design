# word trieval: 单词索引器
## 分析
### 背景分析
给定一个文本文件，要求统计给定单词在文本中出现的总次数，并检索输出某个单词出现在文本中的行号、在该行中出现的次数以及位置。

在自然语言处理中，经常要处理这样的多个单词词语，统计并分析出一定的结论，可以采取哈希表、字典树等数据机构来存储
### 功能分析
1. 索引器需要能够提取出所有的单词，并对其的数量进行统计。
2. 索引器在搜索后支持 "查"的查询功能，能够查询索引器来处理
3. 索引器可以绕过那些非单词，比如标点符号和a等特殊符号
4. 需要把单词统一转换成一种形式，比如大写全部转化为小写

## 设计
### 数据结构设计
#### Record
记录单个单词的行列信息

|  类型      |   字段名        | 功能 |
| ------------- |:-------------:| :-----:|
| int| line| 记录单词行号|
| int| position| 记录单词列号|

#### WordRecord
用于记录一个单词出现的所有记录，是对Record的封装

字段如下 

|  类型      |   字段名        | 功能 |
| ------------- |:-------------:| :-----:|
|std::vector<Record>  |word_record | 记录所有单词|

API如下

|  声明     | 功能 |
| ------------- |:-------------:|
|void output_line_records(int line) |输出给定的一行的记录| 
| void push_back_record(const Record& record)|加入必定有序的记录|
| int counts()| 返回这个单词出现的次数|
|void show_all()|显示一个单词出现的所有情况，用于调试|


#### WordRecords:在map中针对单词的记录
对所有的单词进行记录

##### 字段与API

|  声明     | 功能 |PUBLIC／PRIVATE|
| ------------- |:-------------:| :----:|
| std::map<Word, WordRecord, wordcomp>|专门针对某个单词计数 |PRIVATE|
| void add_record(const Word& word, int line, int position)|添加一个档次的一条记录| PUBLIC|
| int count_times(const Word& word)|针对某个单词，返回这个单词出现的次数|PUBLIC|
|void show_word(const Word& word)|打印一个档次出现的全部情况，用于调试|PUBLIC|

#### WordTokenizer
根据输入的包含大写、标点符号、换行符的字符串产生对应单词的类

##### 字段
|  类型     | 功能 | 字段名| 
| ------------- |:-------------:|:---: |
| const std::string| 记录需要处理的字符串 | line|
| int | 表示处理的位置 | cur_pos |
| static std::set<char>| 记录能够被作为单词的char集合，用于提取出单词 |  alphabet |

##### API
|  声明     | 功能 |PUBLIC／PRIVATE|
| ------------- |:-------------:| :----:|
| static bool in_alphabet(char ch)| 检测给出的单词是否在单词集合中，用于判定| Private|
|bool get_word(Word& word) |把一个新的单词写入给出的参数，并返回是否成功写入，如果单词处理完成，无法写入则返回FALSE |Private|

## 实现
### 读取单词功能实现
#### 读取单词逻辑
1. 从文件流(file_in)中读入数据
2. 对于文件流的每行字符串，创建一个WordTokenizer
3. 利用WordTokenizer, 将输入的字符串流变成单词流
4. 在WordRecords中，添加对应记录

```doxygen
for (int line_pos = 1; getline(file_in, line); ++line_pos) {
    WordTokenizer wordTokenizer(line);
    Word tmp_word;
    for (int pos = 1; wordTokenizer.get_word(tmp_word); ++pos) {
        records.add_record(tmp_word, line_pos, pos);
    }
}
```
将每一行在WordTokenizer中读取，并且加入到WordRecords 中

由于此处是顺序添加，可以直接添加

### 提取单词功能实现
Tokenizer需要提取出单词，便于后文处理

```doxygen
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
```

### 单词查询处理
main中单词查询的代码

```doxygen
while (true) {
        cout << "请输入你要检索的单词" << '\n';
        cin >> search;
        records.show_word(search);
    }
```
在一个循环中，根据给入的单词，进行查询并打印显示

实际查询的代码如下
```doxygen
void WordRecords::show_word(const Word &word) {
    const auto iter = record_map.find(word);
    if (iter != record_map.end()) {
        return iter->second.show_all();
    }
    std::cout << "There is no word \"" << word << "\"\n";
}
```
在对应的WordRecord对象中查询，并且找到对应的单词即调用低沉的显示，否则打印"不存在这个单词"


## 测试
### 单词读取功能测试
```doxygen
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
```
读取TestData，并且打印其中的所有单词，统计数目

输出(以went为例)
```doxygen
went:
line 52: 
line: 52   position: 2
line 98: 
line: 98   position: 12
line 168: 
line: 168   position: 44
line 208: 
line: 208   position: 14
line 280: 
line: 280   position: 10
```

### 搜索单词功能测试
先如读入单词那样构建好一个WordRecords, 并搜索文本中的magic 和 potter

测试关键代码如下

```doxygen
void SearchTest::main() {
    std::string filename = "/Users/fuasahi/ClionProjects/WordTrieval/Testdata/11.txt";
    std::ifstream file_in(filename);

    std::string line;
    WordRecords records;
    for (int line_pos = 1; std::getline(file_in, line); ++line_pos) {
        WordTokenizer wordTokenizer(line);
        Word tmp_word;
        for (int pos = 1; wordTokenizer.get_word(tmp_word); ++pos) {
            records.add_record(tmp_word, line_pos, pos);
        }
    }
    file_in.close();

    const std::string to_search[] = {"magic", "potter"};

    for (const auto& s: to_search) {
        std::cout << "Word is " << s;
        records.show_word(s);
        std::cout << "\n\n";
    }
}
```

输出结果:
```doxygen
Word is magicThere is no word "magic"


Word is potterline 138: 
line: 138   position: 16
line 142: 
line: 142   position: 21
line 168: 
line: 168   position: 50
line 194: 
line: 194   position: 3
line 274: 
line: 274   position: 20
line: 274   position: 56
line 276: 
line: 276   position: 6
line 280: 
line: 280   position: 24
line: 280   position: 46
line 286: 
line: 286   position: 84
line 340: 
line: 340   position: 16
line 356: 
line: 356   position: 5
line: 356   position: 18
line: 356   position: 22
line 368: 
line: 368   position: 2
line 374: 
line: 374   position: 3
line 378: 
line: 378   position: 7
line 388: 
line: 388   position: 2
```