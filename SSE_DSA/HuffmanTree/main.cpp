#include <iostream>
#include <vector>

#include "HuffmanTree.h"

using namespace std;

int main() {
    int node_times;
    cin >> node_times;
    vector<int> woods(node_times);
    for (int i = 0; i < node_times; ++i) {
        cin >> woods[i];
    }

    auto tree = HuffmanTree(woods);
    cout << tree.getSumValue();
    return 0;
}