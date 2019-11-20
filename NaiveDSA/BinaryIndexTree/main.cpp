#include <iostream>

// counting how many data `x` manages
inline int lowbit(int x) {
  //算出x二进制的从右往左出现第一个1以及这个1之后的那些0组成数的二进制对应的十进制的数
  return x & -x;
}

void add(int x, int k, int n, int c[n]) {
    while (x <= n) {  //不能越界
        c[x] = c[x] + k;
        x = x + lowbit(x);
    }
}

int getsum(int x, int n, int c[n]) {  // a[1]……a[x]的和
    int ans = 0;
    while (x >= 1) {
        ans = ans + c[x];
        x = x - lowbit(x);
    }
    return ans;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}