#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

const int N = 2e6 + 5;
int a[N], b[N];
LL sum[N];

LL gett(LL x) {
    return x * (x + 1) >> 1;
}

class LeftAndRightHandedDiv1 {
public:
    LL countSwaps(string Y, int A, int B, int C, int D, int n) {
	int m = Y.size();
	a[0] = A;
	for (int i = 1; i < n; ++i) 
	    a[i] = ((LL)a[i - 1] * B + C) % D;
	for (int i = 1; i <= n; ++i) 
	    if (Y[a[i - 1] % m] == 'R') { 
		a[i - 1] = 1; 
		b[i] = b[i + n] = 1;
		sum[i] = i;
		sum[i + n] = i + n;
	    }
	    else a[i - 1] = 0;
	for (int i = 1; i <= 2 * n; ++i) {
	    sum[i] += sum[i - 1];
	    b[i] += b[i - 1];
	}
	if (b[n] == n || b[n] == 1 || b[n] == 0) return 0;
	LL ans = 1LL << 60;
	int num = b[n];
	int t = num + 1 >> 1;
	for (int i = 1; i <= n; ++i) 
	    if (a[i - 1] == 1) {
		int L = lower_bound(b + 1, b + 1 + 2 * n, t + b[i - 1]) - b;
		int R = lower_bound(b + 1, b + 1 + 2 * n, num + b[i - 1]) - b;
		LL tmp1 = gett(L) - gett(L - t) - (sum[L] - sum[i - 1]);
		LL tmp2 = (sum[R] - sum[L]) - (gett(L + num - t) - gett(L)); 
		ans = min(ans, tmp1 + tmp2);
	    }
	return ans;
    }
};
