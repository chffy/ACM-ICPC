#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

double dp[2][305][305];
double f[2][305];
int bo[2][305][305];

class WheelofFortune {
public:
    double maxExpectedValue(int n, vector <int> s) {
	memset(dp, 0, sizeof(dp));
	int m = s.size();
	int cur = 0, nex = 1;
	for (int i = 1; i < n; ++i) {
	    dp[cur][i][0] = 0;
	}
	f[cur][0] = 1.0; 
	for (int I = 0; I < m; ++I) {
	    memset(dp[nex], 0, sizeof(dp[nex]));
	    memset(f[nex], 0, sizeof(f[nex]));
	    for (int i = 0; i <= I; ++i) {
			f[nex][i + 1] += 1.0 * s[I] / n * f[cur][i];
			f[nex][i] += 1.0 * (n - s[I]) / n * f[cur][i];
	    }
	    int sum = n;
	    for (int i = 1; i < n; ++i) {
		int num[4];
		double p[4];
		memset(num, 0, sizeof(num));
		for (int j = 0; j < n; ++j) {
			int opt = 0;
			if (j == 0 || j + s[I] - 1 >= n) opt |= 1;
			if (j <= i && j + s[I] - 1 >= i) opt |= 2;
			if (j > i && (j + s[I] - 1) % n >= i && (j + s[I] - 1) >= n) opt |= 2;
			++num[opt];
		}
		p[0] = 1.0 * num[0] / sum;
		p[1] = 1.0 * num[1] / sum;
		p[2] = 1.0 * num[2] / sum;
		//if (num[1] != num[2]) puts("sb");
		p[3] = 1.0 * num[3] / sum;
		for (int j = 0; j <= m; ++j) {
		    	dp[nex][i][j] += p[0] * dp[cur][i][j] * f[cur][j];
		    	dp[nex][i][j] += p[2] * (dp[cur][i][j] + 1) * f[cur][j];
		    if (j) { 
		    	dp[nex][i][j] += p[1] * dp[cur][i][j - 1] * f[cur][j - 1];
		   		dp[nex][i][j] += p[3] * (dp[cur][i][j - 1] + 1) * f[cur][j - 1];
		    }
		    if (f[nex][j] != 0) dp[nex][i][j] /= f[nex][j];
		    else dp[nex][i][j] = 0;
		}
	    }

	    swap(cur, nex);
	}
	double ans = 0;
	for (int i = 0; i <= m; ++i) {
	    double ans1 = 0;
	    for (int j = 0; j < n; ++j) {
		double ans2 = dp[cur][j][i];
		ans1 = max(ans2, ans1);
	    }
	    ans += f[cur][i] * i + ans1 * f[cur][i];
	}
	return ans;
    }
};
