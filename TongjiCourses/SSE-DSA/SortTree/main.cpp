#include <iostream>
#include "BinaryTree/BaseTree.h"
#include <random>
#include <iostream>

int main() {
    std::shared_ptr<BaseTree<int>> baseTreePtr = nullptr;
    const char WELCOME[]  =
            "------------------------------\n"
                    "**\t\t 家谱管理系统 \t\t**\n"
                    "**\t\t1.建立二叉排序树\t\t**\n"
                    "**\t\t2.插入元素\t\t\t**\n"
                    "**\t\t3.查询元素\t\t\t**\n"
                    "**\t\t4.退出程序\t\t\t**\n";
    std::cout << WELCOME;

    bool exit_loop(false);
    while (!exit_loop) {
        std::cout << "Please select: ";
        int select;
        std::cin >> select;
        switch (select) {
            case 1:
            {
                baseTreePtr = std::make_shared<BaseTree<int>>();
                std::cout << "Please input the value to insert in bsort tree.\n";
                int reduce(0);
                while (std::cin >> reduce && reduce) {
                    baseTreePtr->insert(reduce);
                }
                baseTreePtr->travelse();
            }
                break;
            case 2:
            {
                if (baseTreePtr == nullptr) {
                    std::cout << "Please first build he tree(using 1)\n";
                    break;
                }
                int to_insert;
                std::cout << "Please input the key to insert: ";
                std::cin >> to_insert;
                baseTreePtr->insert(to_insert);
                baseTreePtr->travelse();
            }
                break;
            case 3:
            {
                if (baseTreePtr == nullptr) {
                    std::cout << "Please first build he tree(using 1)\n";
                    break;
                }
                int to_search;
                std::cout << "Please input the key to search: ";
                std::cin >> to_search;
                auto node = baseTreePtr->find(to_search);
                if (node == nullptr) {
                    std::cout << "Value " << to_search << " is not in the tree\n";
                } else {
                    std::cout << "Search success.\n";
                }
            }
                break;
            case 4:
                exit_loop = true;
                break;
        }
    }

    return 0;
}