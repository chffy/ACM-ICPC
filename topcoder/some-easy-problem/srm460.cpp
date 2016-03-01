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

int f[10][1 << 9];
int bo[1 << 9];

class TheQuestionsAndAnswersDivOne {
public:
    int find(int qs, vector <string> as) {
        int m = as.size();
        for (int i = 1; i < 1 << m; ++i) {
            int flag = 0;
            for (int j = 0; j < m; ++j)
                if (i >> j & 1) {
                    if (as[j] == "Yes") flag |= 1;
                    else flag |= 2;
                }
            if (flag != 3) bo[i] = 1; 
        }
        f[0][0] = 1;
        for (int i = 1; i <= qs; ++i)
            for (int mask = 0; mask < 1 << m; ++mask) {
                int opt = ((1 << m) - 1) ^ mask;
                for (int k = opt; k > 0; k = (k - 1) & opt) {
                    if (bo[k])
                        f[i][k | mask] += f[i - 1][mask];
                }
            }
        return f[qs][(1 << m) - 1];
    }
};
