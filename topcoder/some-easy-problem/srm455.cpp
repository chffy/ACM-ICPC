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

int mp[55][55];
int f[55][55][55][55];

int dfs(int l1, int r1, int l2, int r2) {
    if (f[l1][r1][l2][r2] != -1) return f[l1][r1][l2][r2];
    if (l2 - l1 < 2 || r2 - r1 < 2) return f[l1][r1][l2][r2] = 0;
    int &tmp = f[l1][r1][l2][r2];
    tmp = max(dfs(l1 + 1, r1, l2, r2), dfs(l1, r1 + 1, l2, r2));
    tmp = max(tmp, max(dfs(l1, r1, l2 - 1, r2), dfs(l1, r1, l2, r2 - 1)));
    int flag = 1;
    for (int i = r1; i <= r2 && flag; ++i)
        if (mp[l1][i] == 0 || mp[l2][i] == 0) flag = 0;
    for (int i = l1; i <= l2 && flag; ++i)
        if (mp[i][r1] == 0 || mp[i][r2] == 0) flag = 0;
    if (flag) tmp = max(tmp, dfs(l1 + 1, r1 + 1, l2 - 1, r2 - 1) + 1);
    return tmp;
}

class DonutsOnTheGridEasy {
public:
    int calc(vector <string> grid) {
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                mp[i][j] = (grid[i][j] == '0');
        memset(f, -1, sizeof(f));
        return dfs(0, 0, n - 1, m - 1);
    }
};
