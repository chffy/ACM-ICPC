#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int grid[105][105];
const int P = 1e9 + 7;
typedef long long LL;
int mark[105][105][2];
const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

int num[20][20][3];

class MagicalGirlLevelTwoDivOne {
public:
    int theCount(vector <string> palette, int n, int m) {
        int h = palette.size(), w = palette[0].size();
        int ans = 1;
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) {
                if (palette[i][j] == '.') {
                    grid[i][j] = 2;
                }
                else grid[i][j] = (palette[i][j] - '0') & 1;
                ++num[i % n][j % m][grid[i][j]];
            }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                mark[i][j][0] = mark[i][j][1] = 1;
                if (num[i][j][0] > 0 && num[i][j][1] > 0)
                    return 0;
                int k0 = 1, k1 = 1;
                for (int k = 0; k < num[i][j][2]; ++k) {
                    k0 = (LL)k0 * 4 % P;
                    k1 = (LL)k1 * 5 % P;
                }
                if (num[i][j][0] > 0) {
                    mark[i][j][0] = k0;
                    mark[i][j][1] = 0;
                }
                else if (num[i][j][1] > 0) {
                    mark[i][j][1] = k1;
                    mark[i][j][0] = 0;
                }
                else {
                    mark[i][j][0] = k0;
                    mark[i][j][1] = k1;
                }
            }
        static int dp[2][1 << 10], cost[10][1 << 10];
        for (int i = 0; i < n; ++i) {
            for (int mask = 0; mask < 1 << m; ++mask) {
                cost[i][mask] = 1;
                for (int j = 0; j < m; ++j)
                    cost[i][mask] = (LL)cost[i][mask] * mark[i][j][mask >> j & 1] % P;
            }
        }
        memset(dp, 0, sizeof(dp));
        int cur = 0, nex = 1;
        dp[cur][0] = 1;
        for (int i = 0; i < n; ++i) {
            memset(dp[nex], 0, sizeof(dp[nex]));
            for (int mask = 0; mask < 1 << m; ++mask)
                if (dp[cur][mask])
                    for (int opt = 0; opt < 1 << m; ++opt)
                        if ((__builtin_popcount(opt) & 1)){
                            int tmp = (LL)dp[cur][mask] * cost[i][opt] % P;
                            dp[nex][opt ^ mask] = (dp[nex][opt ^ mask] + tmp) % P;
                        }
            swap(cur, nex);
        }
        return (LL)dp[cur][(1 << m) - 1] * ans % P;
    }
};
