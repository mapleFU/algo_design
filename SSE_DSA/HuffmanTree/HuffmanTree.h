//
// Created by 付旭炜 on 2017/10/11.
//

#ifndef HUFFMANTREE_HUFFMANTREE_H
#define HUFFMANTREE_HUFFMANTREE_H

#include <vector>
#include <queue>

struct node {
    node* left, *right;
    int value;
    bool isLeaf() {
        return (left == nullptr && right == nullptr);
    }
    bool operator<(const node& that) { return this->value < that.value; }
    explicit node(int _value): value(_value) {
        left = right = nullptr;
    }
};

class HuffmanTree {
private:
    node* root;
    node* buildHuffmanTree(std::vector<int>& nodes);
    void clear_node(node* root);
    int getSumValue(node* root);
public:
    explicit HuffmanTree(std::vector<int>& lengths) { root = nullptr; buildHuffmanTree(lengths); }
    HuffmanTree() = delete;
    int getSumValue() { return getSumValue(root);}
    ~HuffmanTree() {
        clear_node(root);
    }
};


#endif //HUFFMANTREE_HUFFMANTREE_H
