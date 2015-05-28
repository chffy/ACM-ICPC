#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5 + 5;
int f[2][N];
int num[1 << 3][N];
const int cnt[8] = {0, 1, 1, 2, 1, 2, 2, 3};
const int P = 1e9 + 7;
typedef long long LL;
int I[N], p[N];

class SRMIntermissionPhase {
public:

    void init() {
	I[0] = I[1] = p[0] = p[1] = 1;
	for (int i = 2; i < N; ++i) {
	    I[i] = (LL)(P - P / i) * I[P % i] % P;
	    p[i] = i;
	}
	for (int i = 2; i < N; ++i) {
	    I[i] = (LL)I[i - 1] * I[i] % P;
	    p[i] = (LL)p[i - 1] * p[i] % P;
	}
    }

    int C(int n, int m) {
	if (n < m) return 0;
	return (LL)p[n] * I[m] % P * I[n - m] % P; 
    }

    int countWays(vector <int> p, vector <string> d) {
	int n = d.size();
	init();
	reverse(d.begin(), d.end());
	num[0][0] = 1;
	for (int i = 1; i < 1 << 3; ++i) {
	    for (int j = 1; j < N; ++j) {
		for (int k = 0; k < 1 << 3; ++k) {
		    if ((k & i) != k) continue;
		    int J = j;
		    for (int l = 0; l < 3; ++l) {
			if (!((k >> l) & 1)) continue;
			J -= p[l];
		    }
		    int m = 1;
		    if (cnt[k] & 1) m = -1;
		    num[i][j] += m * C(J - 1, cnt[i] - 1);
		    if (num[i][j] < 0) num[i][j] += P;
		    if (num[i][j] >= P) num[i][j] -= P;
		}
	    }
	}
	int cur = 0, nex = 1;
	memset(f, 0, sizeof(f));
	for (int i = 0; i < N; ++i)
	    f[cur][i] = 1;
	for (int i = 0; i < n; ++i) {
	    memset(f[nex], 0, sizeof(f[nex]));
	    int t = 0;
	    for (int j = 0; j < 3; ++j) 
		if (d[i][j] == 'Y') {
		    t ^= 1 << j;
		}
            int M = 0;
	    for (int j = 1; j < N; ++j) { 
		f[nex][j] = (LL)f[cur][j - 1] * num[t][j - 1] % P;
                if (f[nex][j]) M = max(M, j);
            }
	    swap(cur, nex);
	    for (int j = 1; j < N; ++j) {
		f[cur][j] += f[cur][j - 1];
		f[cur][j] %= P;
	    }
	}
	int ans = f[cur][N - 1];
	return ans;
    }
};
