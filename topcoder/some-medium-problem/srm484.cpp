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

const int P = 1e9 + 7;

int bo[1005][1005];
int dp[1005][1005];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int dfs(int n, int m, int L) {
    if (m > n) return 0;
    if (bo[n][m]) return dp[n][m];
    bo[n][m] = 1;
    if (n == 0) return dp[n][m] = 1;
    if (m == 0) return dp[n][m] = (LL)dfs(n - 1, L - 1, L) * 4 % P;
    return dp[n][m] = (dfs(n - 1, m - 1, L) + (LL)dfs(n - 1, m + L - 1, L) * 3) % P;
}

class PuyoPuyo {
public:
    int theCount(int L, int n) {
        return dfs(n, 0, L);
    }
};
