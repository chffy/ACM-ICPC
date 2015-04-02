#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
int f[3000], g[3000];
int C[3000][3000];

const int P = 555555555;

void solve(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

class XorBoard {
public:
    int count(int H, int W, int Rcount, int Ccount, int S) {
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	for (int i = 0; i < 3000; ++i)
	    for (int j = 0; j <= i; ++j)
		C[i][j] = (j == 0) ? 1 : (C[i - 1][j] + C[i - 1][j - 1]) % P;
	for (int i = 0; i <= min(H, Rcount); ++i) {
	    if ((Rcount - i) & 1) continue;
	    f[i] = C[H][i];
	    int x = (Rcount - i) / 2;
	    f[i] = (LL)f[i] * C[x + H - 1][H - 1] % P;
	}
	for (int i = 0; i <= min(W, Ccount); ++i) {
	    if ((Ccount - i) & 1) continue;
	    g[i] = C[W][i];
	    int x = (Ccount - i) / 2;
	    g[i] = (LL)g[i] * C[x + W - 1][W - 1] % P;
	}
	int ans = 0;
	for (int i = 0; i <= H; ++i) 
	    for (int j = 0; j <= W; ++j) {
		int t = i * W + j * H - 2 * i * j;
		if (t != S) continue;
		ans += (LL)f[i] * g[j] % P;
		//printf("%d %d %d %d\n", i, j, f[i], g[j]);
		ans %= P;
	    }
	return ans;
    }
};
