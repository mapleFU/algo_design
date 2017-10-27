#include <iostream>
#include "FmailyTree.h"
#include <cctype>

using namespace std;

int main() {
    auto tree = FmailyTree::build_family_tree();

    std::string operation_code; // 操作对应码
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
    }
    return 0;
}