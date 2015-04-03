#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 1e6 + 6;

LL a[N];
int b[N];
LL sum[N];

class TheDivisionGame {
public:
    LL countWinningIntervals(int L, int R) {
	int n = R - L + 1;
	for (int i = 0; i < n; ++i)
	    a[i] = i + L, b[i] = 0;
	for (int i = 2; i < 40000; ++i) {
	    int p1 = (L + i - 1) / i;
	    int p2 = R / i;
	    for (int j = p1; j <= p2; ++j) {
		int k = j * i - L;
		while (a[k] % i == 0) {
		    a[k] /= i;
		    ++b[k];
		} 
	    }
	}
	for (int i = 0; i < n; ++i)
	    if (a[i] != 1) b[i] ++;
	memset(sum, 0,sizeof(sum));
	LL ans = (LL)n * (n + 1) / 2;
	sum[0] = 1;
	for (int i = 0; i < n; ++i) {
	    if (i) b[i] ^= b[i - 1];
	    ans = ans - sum[b[i]];
	    sum[b[i]]++;
	}
	return ans;
    }
};