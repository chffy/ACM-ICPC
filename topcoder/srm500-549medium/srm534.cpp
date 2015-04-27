#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
using namespace std;

typedef long long LL;
int bo[100000];
int num[1000], mark[1000];
int opt[1000], m, n, r;

void gett(int x, LL &N) {
    if (x == 1) {
	++r;
	return ;
    }
    opt[n] = 0;
    for (int i = 2; i * i <= x; ++i)
	if (!bo[i] && x % i == 0) {
	    int j;
	    for (j = 0; j < m; ++j)
		if (mark[j] == i) break;
	    if (j >= m) return ;
	    int t = 0;
	    while (x % i == 0) {
		++t;
		x /= i;
	    }
	    if (t != num[j]) return ;
	    opt[n] |= 1 << j;
	}
    if (x != 1) {
	int j;
	if (N % x == 0) {
		mark[m] = x;
		while (N % x == 0) {
			++num[m];
			N /= x;
		}
		++m;
	}
	for (j = 0; j < m; ++j)
	    if (mark[j] == x) break;
	if (j >= m) return ;
	if (num[j] != 1) return ;
	opt[n] |= 1 << j;
    }
    ++n;
}

LL dp[2][1 << 16];

class EllysNumbers {
public:
    LL getSubsets(LL N, vector <string> special) {
	m = n = r = 0;
	for (int i = 2; i < 100000; ++i) 
	    if (!bo[i]) {
		if (N % i == 0) {
		    mark[m] = i; 
		    while (N % i == 0) {
			N /= i;
			++num[m];
		    }
		    m++;
		}
		for (int j = i * 2; j < 100000; j += i)
		    bo[j] = 1;
	    }
	string S = "";
	for (int i = 0; i < special.size(); ++i)
	    S += special[i];
	for (int i = 0; i < S.size(); ++i) 
	    if (S[i] != ' ') {
		int x = S[i] - '0';
		while (i + 1 < S.size() && isdigit(S[i + 1]))
		    x = x * 10 + S[++i] - '0';
		gett(x, N);
	}
	if (N != 1) return 0;
	int cur = 0, nex = 1;
	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
	    memset(dp[nex], 0, sizeof(dp[nex]));
	    for (int mask = 0; mask < 1 << m; ++mask)
		if (dp[cur][mask]) {
		    dp[nex][mask] += dp[cur][mask];
		    if ((mask & opt[i]) == 0)
			dp[nex][mask | opt[i]] += dp[cur][mask];
		}
	    swap(cur, nex);
	}
	LL ans = dp[cur][(1 << m) - 1];
	for (int i = 1; i <= r; ++i)
	    ans = ans * 2;
	return ans;
    }
};
