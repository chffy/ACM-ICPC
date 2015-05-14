#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

const int P = 1e9 + 7;
int f[55][55], g[55][2], t[55];
typedef long long LL;

class BricksN {
public:
    int countStructures(int w, int h, int K) {
        for (int i = 0; i <= w; ++i)
            f[0][i] = 1;
        t[0] = 1;
        for (int i = 1; i <= w; ++i)
            for (int j = 1; j <= K && j <= i; ++j)
                t[i] = (t[i] + t[i - j]) % P;
        for (int i = 1; i <= h; ++i) {
            memset(g, 0, sizeof(g));
            g[0][0] = 1;
            for (int j = 1; j <= w; ++j) {
                g[j][0] = (g[j - 1][0] + g[j - 1][1]) % P;
                for (int k = 1; k <= j; ++k)
                    g[j][1] = (g[j][1] + (LL)g[j - k][0] * f[i - 1][k] % P * t[k]) % P;
                f[i][j] = (g[j][0] + g[j][1]) % P;
            }
        }
        return f[h][w];
    }
};
