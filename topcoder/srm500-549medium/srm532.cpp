#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int P = 1e9 + 7;
int dp[31][31][1 << 8];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int C[100][100];

int count(int n, int m) {
    if (n == 0 && m == 0) return 1;
    return C[n + m - 1][n - 1];
}

class DengklekBuildingRoads {
public:
    int numWays(int n, int m, int K) {
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for (int i = 0; i < 100; ++i)
            for (int j = 0; j <= i; ++j)
                C[i][j] = (j == 0) ? 1 : (C[i - 1][j - 1] + C[i - 1][j]) % P;
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j <= m; ++j)
		for (int mask = 0; mask < 1 << K; ++mask)
		    if (dp[i][j][mask]) {
                        //printf("%d %d %d\n", i, j, mask);
			int res = dp[i][j][mask];
			int p = min(i, K);
			for (int k = 0; k < 1 << p; ++k) {
			    int sum = j + __builtin_popcount(k);
			    if (sum > m) continue;
			    int mask1 = mask ^ k;
			    int edge = __builtin_popcount(k) & 1;
			    if ((mask1 >> (K - 1)) & 1) continue;
			    for (int l = 0; sum + l * 2 <= m; ++l)
			    	updata(dp[i + 1][sum + l * 2][(mask1 << 1) | edge], (long long)res * count(p, l) % P);
			}
		    }
	return dp[n][m][0];
    }
};
