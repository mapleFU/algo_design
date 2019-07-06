//
// Created by 付旭炜 on 2019/4/3.
//

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

constexpr int MAX_DELTA = 10000000;

int count_min_ret(vector<int>& sumstack) {
    int cmin = MAX_DELTA;
    int cmax = -MAX_DELTA;
    for (int i = 0; i < sumstack.size(); ++i) {
        if (sumstack[i] > cmax) {
            cmax = sumstack[i];
        }
        if (sumstack[i] < cmin) {
            cmin = sumstack[i];
        }
    }
    return cmax - cmin;
}

int dfs(const vector<int>& data, vector<bool>& used_boolean, int used_data, int size, vector<int>& sumstack) {
    int min_ret = MAX_DELTA;
    if (used_data == size) {
//        cout << "Touch the bottom" << '\n';
        return count_min_ret(sumstack);
    }

    for (int i = 0; i < size; ++i) {
        // i used
        if (used_boolean[i]) {
            continue;
        }
        for (int j = i + 1; j < size; ++j) {
            // j used
            if (used_boolean[j]) {
                continue;
            }

            used_boolean[i] = true;
            used_boolean[j] = true;
            int current_sum = data[i] + data[j];
//            cout << current_sum << '\n';
            sumstack.push_back(current_sum);

            int current = dfs(data, used_boolean, used_data + 2, size, sumstack);
            if (min_ret > current) {
                min_ret = current;
            }

            used_boolean[i] = false;
            used_boolean[j] = false;
            sumstack.pop_back();
        }
    }
    return min_ret;
}


int main() {

    int array_size;
    cin >> array_size;
    vector<int> arrvec(array_size);
    vector<bool> boolvec(array_size, false);
//    vector<int> sumstack(array_size);
    vector<int> sumstack;
    int current;
    for (int i = 0; i < array_size; ++i) {
        cin >> current;
        arrvec[i] = current;
    }
    cout << dfs(arrvec, boolvec, 0, array_size, sumstack) << '\n';


}