#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

LL f[N][1 << 3];

class AlternateColors2 {
public:
    LL countWays(int n, int k) {
        f[0][7] = 1;
        for (int i = 0; i < n; ++i)
            for (int mask = 0; mask < 1 << 3; ++mask)
                if (f[i][mask])
                    for (int opt = mask; opt; opt = (opt - 1) & mask) {
                        int num = __builtin_popcount(opt);
                        if (i + num > n) continue;
                        if (i < k) {
                            if (i + num >= k) {
                                if ((opt & 1) && (k - i == 1)) {
                                    f[i + num][opt] += f[i][mask];
                                }
                            }
                            else {
                                f[i + num][opt] += f[i][mask];
                            }
                        }
                        else {
                            f[i + num][opt] += f[i][mask];
                        }
                    }
        LL ans = 0;
        for (int i = 0; i < 1 << 3; ++i)
            ans += f[n][i];
        return ans;
    }
};
