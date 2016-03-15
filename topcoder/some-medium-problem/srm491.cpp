#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
using namespace std;

typedef long long LL;

int num[1 << 16][26], len[16], lcp[1 << 16];
int n, f[55][1 << 16];

int dp(int x, int mask) {
    if (f[x][mask] != -1) return f[x][mask];
    if (mask == 0) return f[x][mask] = 0;
    for (int i = 0; i < n; ++i)
        if ((mask >> i & 1) && len[i] <= x) {
            return f[x][mask] = dp(x, mask ^ (1 << i));
        }
    if (lcp[mask] > x) return f[x][mask] = dp(x + 1, mask) + 1;
    f[x][mask] = 1 << 30;
    for (int opt = mask; opt != 0; opt = (opt - 1) & mask) {
        if (lcp[opt] <= x) continue;
        f[x][mask] = min(f[x][mask], dp(x + 1, opt) + 1 + dp(x, mask ^ opt));
    }
    return f[x][mask];
}

class PrefixTree {
public:
    int getNumNodes(vector <string> words) {
        n = words.size();
        for (int i = 0; i < n; ++i) {
            for (auto ch : words[i]) 
                num[1 << i][ch - 'a']++;
            len[i] = words[i].size(); 
        }
        for (int mask = 1; mask < 1 << n; ++mask)
            if (__builtin_popcount(mask) != 1) {
                int x = mask & -mask;
                for (int i = 0; i < 26; ++i)
                    num[mask][i] = min(num[x][i], num[mask ^ x][i]);
            }
        for (int mask = 0; mask < 1 << n; ++mask)
            for (int i = 0; i < 26; ++i)
                lcp[mask] += num[mask][i];
        memset(f, -1, sizeof(f));
        return dp(0, (1 << n) - 1) + 1;
    }
};
