//
// Created by 付旭炜 on 2019/3/6.
//
#include <iostream>
#include <iostream>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
      if(num1 == "0" || num2 == "0")
        return "0";
      int size1 = num1.size(), size2 = num2.size();
      string str(size1 + size2, '0');
      for(int i = size1 - 1; i >= 0; i--){
        int mulflag = 0;
        int addflag = 0;
        for(int j = size2 - 1; j >= 0; j--){
          int tmp = (num1[i] - '0') * (num2[j] - '0') + mulflag;
          mulflag = tmp / 10;
          tmp  = tmp % 10;
          int tmp2 = str[i + j + 1] - '0' + tmp + addflag;
          str[i + j + 1] = tmp2 % 10 + '0';
          addflag = tmp2 / 10;
        }
        str[i] += mulflag + addflag;
      }
      if (str[0] == '0')
        str = str.substr(1, str.size());
      return str;
    }
};

int main() {
  string data1, data2;
  cin >> data1 >> data2;
//  cout << "data1" << data1 << " data2" << data2 << '\n';


  Solution solution;
  string sol = solution.multiply(data1, data2);
//  cout <<  sol << endl;

  // split zero
  int beg_pos = 0;
  if (sol.size() != 1) {
    for (beg_pos = 0; beg_pos < sol.size(); ++beg_pos) {
      if (sol[beg_pos] == '0') {
        continue;
      } else {
        break;
      }
    }
  }

  cout << sol.substr(beg_pos) << '\n';
}