#include <iostream>
#include "src/SystemView.h"

int main() {
    SystemView systemView = SystemView(std::cin);
    systemView.run();
    return 0;
}