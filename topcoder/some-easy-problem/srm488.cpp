#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

double dp[100][100];
int bo[100][100];

double dfs(int n, int m) {
    if (bo[n][m]) return dp[n][m];
    bo[n][m] = 1;
    if (m == 0) return dp[n][m] = 0;
    bo[n][m] = 1;
    int sum = (n + m) * (n + m - 1) / 2;
    int A = n * (n - 1) / 2;
    int B = m * (m - 1) / 2;
    int C = n * m;
    dp[n][m] = (dfs(n + 1, m - 1)  + 1) * C / sum;
    if (m >= 2)
        dp[n][m] += (dfs(n + 2, m - 2) + 1) * B / sum;
    dp[n][m] += (double) A / sum;
    dp[n][m] *= (double)sum / (sum - A);
    //printf("%d %d %.10f %d %d %d\n", n, m, dp[n][m], A, B, C);
    return dp[n][m];
}

class TheBoredomDivOne {
public:
    double find(int n, int m) {
        return dfs(n, m);
    }
};
