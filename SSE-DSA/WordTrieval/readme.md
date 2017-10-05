# word trieval: 单词索引器
## UTIL: 组件介绍
### MyMap:自己实现的存储、索引表
MyMap:范型的\<KET-VALUE\>存储表，用于存储数据，内部采用散列表实现
### WordRecords:在map中针对单词的记录
Word: 用来表示单词，借助了`std::string`来实现
Record: 表示在哪个位置出现的**单个记录**
WordRecords: 当个单词的记录汇总, 记录有大量RECORD, 能够显示单词具体出现的情况
### TrieRecorder: 单词的记录者，程序的主要执行者
WordTokenizer: 接受输入流，产生单词
TrieRecorder: 接受表示输入的文件名称的字符串构造。根据WordTokenizer, 记录这些数据并且存入MyMap
