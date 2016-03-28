#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
#include <deque>
using namespace std;

int f[2][1 << 19], D = 9, S = D * 2 + 1;
int cnt[1 << 19], LOG[1 << 19];

void updata(int &x, int y) {
    x = min(x, y);
}

class Bribes {
public:
    int minBribes(vector <int> inf, vector <int> rest) {
        int n = inf.size();
        for (int i = 0; i < 19; ++i)
            LOG[1 << i] = i;
        int cur = 0, nex = 1;
        memset(f[cur], 63, sizeof(f[cur]));
        f[cur][0] = 0;
        int M = (1 << S) - 1;
        for (int i = 0; i < n + D; ++i) {
            memset(f[nex], 63, sizeof(f[nex]));
            for (int mask = 0; mask <= M; ++mask)
                if (f[cur][mask] <= n) {
                    updata(f[nex][(mask << 1) & M], f[cur][mask]);
                    if (i < n)
                        updata(f[nex][((mask << 1) & M) | 1], f[cur][mask] + 1);
                }
            if (i - D >= 0) {
                memset(cnt, 0, sizeof(cnt));
                for (int mask = 1; mask <= M; ++mask) {
                    int x = LOG[mask & -mask], val = 0;
                    if (i - x >= 0 && i - x < n)
                        val = inf[i - x] >> abs(D - x);
                    cnt[mask] = cnt[mask ^ (1 << x)] + val;
                }
                for (int mask = 0; mask <= M; ++mask)
                    if (cnt[mask] < rest[i - D]) f[nex][mask] = n + 1;
            }
            swap(cur, nex);
        }
        int ans = n + 1;
        for (int mask = 0; mask <= M; ++mask) {
            ans = min(ans, f[cur][mask]);
        }
        if (ans > n) ans = -1;
        return ans;
    }
};
