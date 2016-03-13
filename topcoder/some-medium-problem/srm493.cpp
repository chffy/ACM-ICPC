#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int f[2][1000000], power[10];

class AmoebaCode {
public:
    int find(string code, int K) {
        int n = code.size();
        power[0] = 1;
        for (int i = 1; i < 10; ++i)
            power[i] = power[i - 1] * K;
        for (int t = K; t >= 1; --t) {
            int cur = 0, nex = 1;
            memset(f[cur], 0, sizeof(int) * power[t]);
            f[cur][0] = 1;
            int S = t - 1;
            for (int i = 0; i < n; ++i) {
                memset(f[nex], 0, sizeof(int) * power[S]);
                for (int mask = 0; mask < power[S]; ++mask) {
                    if (!f[cur][mask]) continue;
                    int bo[10];
                    memset(bo, 0, sizeof(bo));
                    for (int j = 0; j < S; ++j)
                        if (i - j - 1 >= 0) {
                            int x = mask / power[j] % K;
                            bo[x] = 1;
                        }
                    for (int j = 0; j < K; ++j)
                        if (bo[j] == 0 && (code[i] == '0' || code[i] - '1' == j)) {
                            int opt = mask;
                            if (t > 1) {
                                opt -= mask / power[S - 1] * power[S - 1];
                                opt = opt * K + j;
                            } else opt = 0;
                            f[nex][opt] = 1;
                        }
                }
                swap(cur, nex);
            }
            for (int mask = 0; mask < power[S]; ++mask)
                if (f[cur][mask]) return t;
        }
        return 0;
    }
};
