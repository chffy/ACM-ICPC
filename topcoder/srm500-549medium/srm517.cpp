#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int Q = 1e9 + 7;
int dp[101][101];
bool bo[101][101];
int C[101][101];
typedef long long LL;

int dfs(int n, int low, vector<int> P) {
    int p[51];
    if (bo[n][low]) return dp[n][low];
    int m = 0;
    bo[n][low] = true;
    if (n == 1) return dp[n][low] = 1;
    for (int i = 0; i < P.size(); ++i)
	if (P[i] >= low && P[i] < low + n) 
	    p[m++] = P[i];
    int &res = dp[n][low];
    res = 0;
    for (int i = 0; i < m - 1; ++i) {
	swap(p[i], p[i + 1]);
	int j, k;
	for (j = 0; j <= i; ++j) 
	    if (p[j] > low + i) break;
	for (k = i + 1; k < m; ++k)
	    if (p[k] <= low + i) break;
	if (j > i && k >= m) {
	    int p = (LL)dfs(i + 1, low, P) * dfs(m - i - 1, low + i + 1, P) % Q;
	    // i goods  m - i - 1 boxs C[m - 2][m - i - 2]
	    p = (LL)p * C[m - 2][m - i - 2] % Q;
	    res = (res + p) % Q;
	}
	swap(p[i], p[i + 1]);
    }
    return res;
}

class AdjacentSwaps {
public:
    int theCount(vector <int> p) {
	int n = p.size();
	for (int i = 0; i < 100; ++i)
	    for (int j = 0; j <= i; ++j)
		C[i][j] = (j == 0) ? 1 : (C[i - 1][j] + C[i - 1][j - 1]) % Q;
	memset(bo, false, sizeof(bo));
	dfs(n, 0, p);
	return dp[n][0];
    }
};
