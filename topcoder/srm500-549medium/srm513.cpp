#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

double dp[30][30];
const double esp = 1e-9;

class PerfectMemory {
public:
    double getExpectation(int N, int M) {
	int n = N * M / 2;
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i)
	    for (int j = 0; j <= n * 2; ++j) {
		int sum = i * 2;
		if (j > sum || (j & 1)) continue;
		double &res = dp[i][j];
			res = 1.0 * (sum - j) / (sum * (sum - 1)) * (dp[i - 1][j] + 1);
			res += 1.0 * j / sum * (sum - j) / (sum - 1) * (dp[i - 1][j] + 1);
			if (j >= 2) res += 1.0 * j / sum * (j - 1) / (sum - 1) * (dp[i - 1][j - 2] + 2);
			if (j + 2 <= sum - 2) res += 1.0 * (sum - j) * (sum - j - 1) / sum /(sum - 1) * (dp[i - 1][j + 2] + 1);
	    }
	return dp[n][0];
    }
};
