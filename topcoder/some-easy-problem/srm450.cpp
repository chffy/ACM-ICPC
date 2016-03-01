#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

typedef long long LL;

int f[55][3];

class OrderedNim {
public:
    string winner(vector <int> num) {
        int n = num.size();
        num.push_back(0);
        for (int i = n - 1; i >= 0; --i) {
            if (num[i] == 1) num[i] = 1;
            else num[i] = 2;
            for (int j = 1; j <= num[i]; ++j) {
                for (int k = 1; k <= j; ++k) {
                    if (k != j) f[i][j] |= f[i][j - k] ^ 1;
                    else f[i][j] |= f[i + 1][num[i + 1]] ^ 1;
                }
            }
        }
        if (f[0][num[0]]) return "Alice";
        return "Bob";
    }
};
