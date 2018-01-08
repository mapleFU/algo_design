#include <iostream>
#include "poly.h"

using namespace std;
int main() {
    poly test1("5x^3+3"), test2("6x^3+7+2x^2");
    cout<<"poly1:" <<test1<<endl<< "poly2: "<< test2<<endl;
    poly test3 = test1 * test2;
    poly testAdd = test1 + test2;
    printf("Test multiply: test1 * test2->");
    cout<<(test1 * test2)<<endl;
    printf("Test add: test1 + test2->");
    cout<<(test1 + test2)<<endl;
    printf("Test fac: test1 ^ 5->");
//    cout<<(test2 ^ 3)<<endl;
    cout<<(test1 ^ 5)<<endl;
    return 0;
}