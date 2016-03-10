#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;

const int P = 1e9 + 7, Q = 1e9 + 9;

class FoxStones {
public:
    int getCount(int m, int n, vector <int> sy, vector <int> sx) {
        int r = sx.size();
        vector<ULL> ver;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                ULL S = 0;
                for (int k = 0; k < r; ++k) {
                    int d = max(abs(i - sx[k]), abs(j - sy[k]));
                    S = S * P + d + 10;
                   // printf("%d %d %d\n", i, j, d);
                }
                ver.push_back(S);
            }
        sort(ver.begin(), ver.end());
        int ans = 1;
        for (int i = 0; i < ver.size(); ++i) {
            int j = i;
            while (j + 1 < ver.size() && ver[j + 1] == ver[i])
                ++j;
            for (int k = 1; k <= j - i + 1; ++k)
                ans = (ULL)ans * k % Q;
            i = j;
        }
        return ans;
    }
};
