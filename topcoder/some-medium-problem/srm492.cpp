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

LL grid[55][55];

int gett(string S, int &p) {
    int x = 0;
    while (isdigit(S[p])) {
        x = x * 10 + S[p] - '0';
        ++p;
    }
    return x;
}

LL dp[55][55][55];

class TimeTravellingTour {
public:
    
    LL determineCost(int n, vector <int> cities, vector <string> roads) {
        string S = "";
        for (auto str : roads) S += str;
        memset(grid, 63, sizeof(grid));
        for (int i = 0; i < n; ++i)
        	grid[i][i] = 0;
        for (int p = 0; p < S.size(); ++p) {
            int x = gett(S, p);
            ++p;
            int y = gett(S, p);
            ++p;
            int s = gett(S, p);
            grid[x][y] = grid[y][x] = min((LL)s, grid[x][y]);
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    grid[i][j] = min(grid[i][j], grid[i][k] + grid[k][j]);
        memset(dp, 63, sizeof(dp));
        int m = cities.size();
        for (int j = 0; j < m; ++j) 
            for (int i = j; i >= 0; --i) {
                for (int k = 0; k < n; ++k) {
                    if (i == j) {
                        dp[k][i][j] = min(dp[k][i][j], grid[k][cities[i]]);
                        continue;
                    }
                    for (int l = i; l < j; ++l) {
                        dp[k][i][j] = min(dp[k][i][j], dp[k][i][l] + dp[k][l + 1][j]);
                        dp[k][i][j] = min(dp[k][i][j], dp[k][i][l] + dp[cities[l]][l + 1][j]);
                    }
                }
                for (int k = 0; k < n; ++k)
                    for (int l = 0; l < n; ++l)
                        dp[k][i][j] = min(dp[k][i][j], dp[l][i][j] + grid[l][k]);
            }
        if (dp[0][0][m - 1] >= dp[m][m][m]) return -1;
        return dp[0][0][m - 1];
    }
};

