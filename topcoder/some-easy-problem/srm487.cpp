#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int f[100][2];

class BunnyComputer {
public:
    int getMaximum(vector <int> pre, int m) {
        int n = pre.size();
        int ans = 0;
        ++m;
        for (int t = 0; t < m; ++t) {
            vector<int> p;
            for (int j = t; j < n; j += m)
                p.push_back(pre[j]);
            memset(f, 0, sizeof(f));
            int r = p.size();
            for (int j = 0; j < r; ++j)
                for (int k = 0; k < 2; ++k) {
                    if (j > 0 && k == 0)
                        f[j + 1][1] = max(f[j + 1][1], f[j][k] + p[j] + p[j - 1]);
                    f[j + 1][0] = max(f[j + 1][0], f[j][k]);
                }
            ans += max(f[r][0], f[r][1]);
            //printf("%d %d, %d %d\n", t, r, f[r][0], f[r][1]);
           // for (int i)
        }
        return ans;
    }
};
