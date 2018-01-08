//
// Created by 付旭炜 on 2017/10/11.
//

#include "HuffmanTree.h"

node *HuffmanTree::buildHuffmanTree(std::vector<int> &nodes) {
    std::priority_queue<node*> pq;
    for(auto value: nodes) {
        pq.push(new node(value));
    }

    while (pq.size() != 1) {
        auto v1 = pq.top();
        pq.pop();
        auto v2 = pq.top();
        pq.pop();
        auto newnode = new node(v1->value + v2->value);
        newnode->left = v1;
        newnode->right = v2;
        pq.push(newnode);
    }

    root = pq.top();
    return root;
}

void HuffmanTree::clear_node(node *root) {
    if (root == nullptr) {
        return;
    } else if (root->isLeaf()) {
        delete root;
        return;
    } else {
        clear_node(root->left);
        clear_node(root->right);
        delete root;
    }
}

int HuffmanTree::getSumValue(node *root) {
    if (root == nullptr) {
        return 0;
    } else if (root->isLeaf()) {
//        delete root;
        return 0;
    } else {
        int value1 = getSumValue(root->left);
        int value2 = getSumValue(root->right);
        return value1 + value2 + root->value;
    }
}
