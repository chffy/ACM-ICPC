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

const int N = 1e6 + 5;
int f[2][N];

class TheSwap {
public:
    int findMax(int n, int K) {
        int cur = 0, nex = 1;
        memset(f[cur], 0, sizeof(f[cur]));
        f[cur][n] = 1;
        int len = 0;
        for (int x = n; x > 0; x /= 10) ++len;
        for (int t = 1; t <= K; ++t) {
            memset(f[nex], 0, sizeof(f[nex]));
            for (int i = 1; i < N; ++i)
                if (f[cur][i]) {
                    for (int j = 0, x = i, p1 = 1; j < len; ++j, x /= 10, p1 *= 10)
                        for (int k = 0, y = i, p2 = 1; k < j; ++k, y /= 10, p2 *= 10) {
                            if (y % 10 == 0 && j == len - 1) continue;
                            int res = i - x % 10 * p1 - y % 10 * p2;
                            res += y % 10 * p1 + x % 10 * p2;
                            //cout << p1 << " " << res << endl;
                            f[nex][res] = 1;
                        }
                }
            swap(cur, nex);
        }
        int ans = -1;
        for (int i = 1; i < N; ++i)
            if (f[cur][i]) ans = max(ans, i);
        return ans;
    }
};
