#include <iostream>
#include "poly.h"
#include "CounterBuilder.h"

using namespace std;
int main() {
    CounterBuilder builder(4, 2, 2);
    builder.run();
    builder.print_all();

    string if_continue;
    std::cout << "按exit并回车退出，按1并回车继续\n";
    while (std::cin >> if_continue) {
        if (if_continue == "exit") {
            break;
        } else if (if_continue != "1") {
            std::cout << "请输入exit或者1\n";
            continue;
        }
        std::cout << "请输入一元 两元 五元纸币数量\n";
        int b1, b2, b5;
        std::cin >> b1 >> b2 >> b5;
        if (b1 >= 0 && b2 >= 0 && b5 >= 0) {
            CounterBuilder builder1(b1, b2, b5);
            builder1.run();
            builder1.print_all();
        } else {
            std::cout << "确保输入的所有数大于1\n";
        }
    }
    return 0;
}