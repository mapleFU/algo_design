/*
 * TODO: 可以考虑对多个重复名字的情况进行处理
 */
#include <iostream>
#include <cctype>

#include "FmailyTree.h"
#include "Hint.h"

using namespace std;

int main() {
    cout << WELCOME;
    auto tree = FmailyTree::build_family_tree();

    std::string operation_code; // 操作对应码

    cout << OPERATES;
    while (cin >> operation_code && operation_code != "E") {

        switch (toupper(operation_code[0])) {
            case 'A':
                tree->create_family();
                break;
            case 'B':
                tree->add_children();
                break;
            case 'C':
                tree->break_family();
                break;
            case 'D':
                tree->modify_name();
                break;
            default:
                std::cout << "Wrong Input!\n";
        }
#ifdef FAMILY_TREE_DEBUG
        tree->show_family();
#endif
        cout << OPERATES;
    }
    return 0;
}