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

typedef long long LL;

int grid[105][105];

LL dp[55][4];
int tmp[105][105];

int n, m;

int sum[55][55][100];

int check(int x, int y, int ch) {
    if (grid[x][y] == '?' || grid[x][y] == ch) return 1;
    return 0;
}

LL dfs(int x, int y) {
    if (y == m) {
        ++x; y = 0;
    }
    if (x >= n) return 1;
    LL ans = 0;
    for (int i = 0; i < 2; ++i) {
        int ch = 'W';
        if (i == 1) ch = 'B';
        if (!check(x, y, ch)) continue;
        tmp[x][y] = ch;
        int flag = 0;
        for (int j = 0; j < y; ++j)
            if (tmp[x][j] == tmp[x][y]) {
                if (sum[j][y][ch]) {
                    flag = 1;
                    break;
                }
            }
        if (flag) continue;
        for (int j = 0; j < y; ++j)
            if (tmp[x][j] == tmp[x][y]) ++sum[j][y][ch];
        ans += dfs(x, y + 1);
        for (int j = 0; j < y; ++j)
            if (tmp[x][j] == tmp[x][y]) --sum[j][y][ch];
    }
    return ans;
}

class RectangleAvoidingColoring {
public:
    LL count(vector <string> board) {
        n = board.size(), m = board[0].size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = board[i][j];
        if (n < m) {
            static int tmp[105][105];
            memcpy(tmp, grid, sizeof(tmp));
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    grid[j][i] = tmp[i][j];
            swap(n, m);
        }
        if (m == 1) {
            LL ans = 1;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    if (grid[i][j] == '?') ans *= 2;
            return ans;
        }
        if (m == 2) {
            dp[0][0] = 1;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < 4; ++j) {
                    if (!dp[i][j]) continue;
                    if (check(i, 0, 'B') && check(i, 1, 'W'))
                        dp[i + 1][j] += dp[i][j];
                    if (check(i, 0, 'W') && check(i, 1, 'B'))
                        dp[i + 1][j] += dp[i][j];
                    if (check(i, 0, 'W') && check(i, 1, 'W') && j % 2 == 0)
                        dp[i + 1][j + 1] += dp[i][j];
                    if (check(i, 0, 'B') && check(i, 1, 'B') && (j >> 1 & 1) == 0)
                        dp[i + 1][j + 2] += dp[i][j];
                }
            return dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3];
        }
        if (n * m > 24) return 0;
        return dfs(0, 0);
    }
};
