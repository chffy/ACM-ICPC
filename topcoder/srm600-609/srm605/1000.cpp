#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int dp[205][205][205];
int ll[205], rr[205], pos[205];
const int P = 1e9 + 7;
int n;

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

class AlienAndPermutation {
public:
    int getNumber(vector <int> P, int K) {
	n = P.size();
	for (int i = 0; i < n; ++i) {
	    int x = P[i];
	    pos[x] = i;
	    ll[x] = rr[x] = i;
	    while (ll[x] - 1 >= 0 && P[ll[x] - 1] < x)
		--ll[x];
	    while (rr[x] + 1 < n && P[rr[x] + 1] < x)
		++rr[x];
	}
	for (int i = 1; i <= n; ++i)
	    if (ll[i] <= 0 && i != P[0]) 
		dp[0][i][1] = 1;
	dp[0][n + 1][0] = 1;
	for (int i = 0; i + 1 < n; ++i)
	    for (int j = 0; j <= K; ++j) {	
		for (int k = 1; k <= n; ++k) 
		    if (i + 1 >= ll[k] && i + 1 <= rr[k])
			updata(dp[i + 1][k][j], dp[i][k][j]);
		if (rr[P[i]] >= i + 1)
		    updata(dp[i + 1][P[i]][j + 1], dp[i][n + 1][j]);
		for (int k = 1, res = 0; k <= n; ++k) {
		    if (ll[k] <= i + 1 && rr[k] >= i + 1 && pos[k] > i) {
			if (k != P[i + 1])
			    updata(dp[i + 1][k][j + 1], res);
			else updata(dp[i + 1][n + 1][j], res);
		    }
		    updata(res, dp[i][k][j]);
		    if (k == P[i]) updata(res, dp[i][n + 1][j]);
		}
		for (int k = n, res = 0; k > 0; --k) {
		    if (ll[k] <= i + 1 && rr[k] >= i + 1) {
			if (k != P[i + 1]) updata(dp[i + 1][k][j + 1], res);
			else updata(dp[i + 1][n + 1][j], res);
		    }
		    if (pos[k] <= i) {
			updata(res, dp[i][k][j]);
			if (k == P[i]) updata(res, dp[i][n + 1][j]);
		    }
		}
	    }
	int ans = 0;
	for (int i = 0; i <= K; ++i)
	    for (int j = 1; j <= n + 1; ++j)
		updata(ans, dp[n - 1][j][i]);
	return ans;
    }

};
