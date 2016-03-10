#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int a[1000], b[1000];
int m;
int dp[55][55][55];
int g[55][55];

class WhiteSpaceEditing {
public:
    int getMinimum(vector <int> lines) {
        int n = lines.size();
        for (int i = 0; i < n; ++i)
            b[i] = lines[i];
        b[n] = 0;
        sort(b, b + n + 1);
        m = unique(b, b + n + 1) - b;
        for (int i = 0; i < n; ++i) {
            a[i] = lower_bound(b, b + m, lines[i]) - b;
        }
        memset(dp, 63, sizeof(dp));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                dp[i][i][j] = abs(b[a[i]] - b[j]);
                
        for (int i = n - 1; i >= 0; --i) {
            memset(g, 63, sizeof(g));
            for (int j = i; j < n; ++j) {
            //	printf("%d %d\n", i, j);
                for (int k = 0; k < m; ++k) {
                    g[j][k] = min(g[j][k], dp[i][j][k] + 1);
                    for (int l = i; l < j; ++l)
                        g[j][k] = min(g[j][k], g[l][k] + dp[l + 1][j][k] + 1);
                    dp[i][j][k] = min(dp[i][j][k], g[j][k] - 1);
                }
                for (int k = 1; k < m; ++k)
                    dp[i][j][k] = min(dp[i][j][k], dp[i][j][k - 1] + abs(b[k] - b[k - 1]));
                for (int k = m - 2; k >= 0; --k)
                    dp[i][j][k] = min(dp[i][j][k], dp[i][j][k + 1] + abs(b[k] - b[k + 1]));
                for (int k = 0; k < m; ++k) {
                    g[j][k] = min(g[j][k], dp[i][j][k] + 1);
                    for (int l = i; l < j; ++l)
                        g[j][k] = min(g[j][k], g[l][k] + dp[l + 1][j][k] + 1);
                    dp[i][j][k] = min(dp[i][j][k], g[j][k] - 1);
                }
            }
        }
        return dp[0][n - 1][0];
    }
};

