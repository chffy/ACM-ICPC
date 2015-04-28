#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 500000;

pair<int, int> stack0[2][N], stack1[2][N];
int p[2], q[2], t[2], r[2];
int f[N][2], len;
bool isprime[N];

inline void stapop(pair<int, int> stack[], int &p, int &t, int i) {
    while (p <= t && stack[p].second + len < i)
	++p;
}

inline void stapush(pair<int, int> stack[], int &p, int &t, pair<int, int> x) {
    while (p <= t && stack[t].first <= x.first)
	--t;
    stack[++t] = x;
}

class PrimeCompositeGame {
public:
    int theOutcome(int n, int K) {
	if (n < 2) return 0;
	len = K;
	memset(isprime, true, sizeof(isprime));
	for (int i = 2; i * i < N; ++i)
	    if (isprime[i]) 
		for (int j = i * i; j < N; j += i)
		    isprime[j] = false;
	p[0] = p[1] = q[0] = q[1] = 1; 
	for (int i = 2; i <= n; ++i) {
	    for (int j = 0; j < 2; ++j)
		stapop(stack0[j], p[j], t[j], i), stapop(stack1[j], q[j], r[j], i);
	    if (q[0] <= r[0]) f[i][0] = -stack1[0][q[0]].first + 1;
	    else {
		f[i][0] = 0;
		if (q[1] <= r[1]) f[i][0] = -stack1[1][q[1]].first - 1;
	    }
	    if (p[0] <= t[0]) f[i][1] = -stack0[0][p[0]].first + 1;
	    else {
		f[i][1] = 0;
		if (p[1] <= t[1]) f[i][1] = -stack0[1][p[1]].first - 1;
	    }
	    if (!isprime[i]) {
	    	if (f[i][0] <= 0) stapush(stack0[0], p[0], t[0], make_pair(f[i][0], i));
	    	else stapush(stack0[1], p[1], t[1], make_pair(f[i][0], i));
		}
		if (isprime[i]) {
	    	if (f[i][1] <= 0) stapush(stack1[0], q[0], r[0], make_pair(f[i][1], i));
	    	else stapush(stack1[1], q[1], r[1], make_pair(f[i][1], i));
		}
		//printf("%d %d %d\n", i, f[i][0], f[i][1]);
	}
	return f[n][0];
    }
};
