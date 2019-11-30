# Data format: Rpc protocol

数据格式是一个很重要的东西，我们可能基本上需要：

1. 一个长度前缀，让我们在流式的数据/不定长的数据中 Parse 出整段数据，定义出消息边界，为此：
   1. 我们可能需要 Http Header 那样，`read(LENGTH_HEADER)`, 再通过 parse 这个 header
   2. 如果需要特殊的边界，比如 `a` 作为边界，我们需要合理的方式对这个边界原单词进行转义。
2. 消息表示和结构：
   1. 如果是 binary 我们可能需要 decode
   2. 如果是文本，如何解析这个文本。
3. 消息本身是否加密/压缩
4. 这样的结构用来做什么？OLAP 这种结构的话是否需要多考虑列存？如果不是这种OLAP 模式的应该怎么解析？是为了更改方便还是计算方便？

## 消息的边界

1. 可能会带上一个定长的前缀，代表length:

   ```
   x = read(Header_LENGTH);
   length = reinterpret_cast<int>(x)
   read(length)
   ```

   这样解析消息

2. 准备一定的消息边界，比如 `\r\n`, 这个时候对于原本这些值要提供一定的转义

## 消息的内容

Http 里面很容易用 Json 来表示，但是我们也要考虑：

1. 消息大小
2. 对修改来说是不是方便
3. 对计算来说是不是方便...

我们以后可以介绍一下 Grpc, Apache Arrow 之类的。

## 消息的压缩

为了流量，Hadoop 之类的系统， RPC 的时候会对消息进行压缩

## Varint

我实现了一个简单的 varint, 代码放在[这里](https://github.com/mapleFU/algo_design/tree/master/NaiveDSA/encoding) , 他是 grpc 协议的一部分

* 对 integer 采用 msb 的格式编码，8个 bit 为一个 group, 第一位表示是否完结
* 8个为一个 group
* 采用 zigzag, 把 int 映射到 unsigned int.

