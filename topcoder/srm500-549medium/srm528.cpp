#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
int a[30], b[30];
LL dp[2][1 << 20];
LL f1[1 << 20], f2[1 << 20];
const int P = 40007;

map <ULL, LL> wayss;

inline void updata(LL &x, LL y) {
    x += y;
}

inline void solve(int a[], int n, LL f[]) {
    memset(dp, 0, sizeof(dp));
    int cur = 0, nex = 1;
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
	memset(dp[nex], 0, sizeof(dp[nex]));
	for (int mask = 0; mask < 1 << n; ++mask) {
	    if (!dp[cur][mask]) continue;
	    if (mask == 0) updata(dp[nex][1 << i], dp[cur][mask] * 2);
	    else {
		int lowbit = mask & -mask;
		int j = __builtin_ctz(lowbit);
		if (a[j] == a[i]) updata(dp[nex][mask ^ lowbit], dp[cur][mask]);
		updata(dp[nex][mask | (1 << i)], dp[cur][mask]);
	    }
	}
	swap(cur, nex);
    }
    memcpy(f, dp[cur], sizeof(dp[cur]));
}

class SPartition {
public:
    LL getCount(string s) {
	int n = s.size(), m = n / 2;
	for (int i = 0; i < m; ++i)
	    a[i] = (s[i] == 'o');
	for (int i = 0; i < m; ++i)
	    b[i] = (s[n - i - 1] == 'o');
	solve(a, m, f1);
	solve(b, m, f2);
	for (int i = 0; i < 1 << m; ++i)
	    f2[i] /= 2;
	LL ans = f1[0] * f2[0] * 2;
	for (int mask = 1; mask < 1 << m; ++mask) 
	    if (f2[mask]) {
		ULL sum = 0;
		for (int i = m - 1; i >= 0; --i)
		    if (mask >> i & 1) sum = sum * P + b[i] + 10;
		wayss[sum] += f2[mask];
	    }
	for (int mask = 1; mask < 1 << m; ++mask) 
	    if (f1[mask]) {
		ULL sum = 0;
		for (int i = 0; i < m; ++i)
		    if (mask >> i & 1) sum = sum * P + a[i] + 10;
		ans += f1[mask] * wayss[sum];
	    }
	return ans;
    }
};
