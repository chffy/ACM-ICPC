#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;

struct Matrix {
    int n;
    int a[351];
    
    Matrix() {
	memset(a, 0, sizeof(a));
    }

    Matrix operator * (const Matrix &b) const {
	Matrix c;
	c.n = n;
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < n; ++j) {
		int l = (i + j) % n;
		c.a[l] += (LL)a[i] * b.a[j] % P;
		c.a[l] %= P;
	    }
	return c;
    }

};

Matrix aa, ans, I, c, z;

Matrix power(LL n) {
    ans = I, z = aa;
    for (; n; n /= 2, z = z * z) 
	if (n % 2) ans = ans * z;
    return ans;
}

int f[2][351][351];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int g[2][351];

class PenguinEmperor {
public:
    int countJourneys(int n, LL d) {
	memset(f, 0, sizeof(f));
	int cur = 0, nex = 1;
	for (int i = 0; i < n; ++i)
	    f[cur][i][i] = 1;
	for (int i = 1; i <= n; ++i) {
	    memset(f[nex], 0, sizeof(f[nex]));
	    for (int j = 0; j < n; ++j)
		for (int k = 0; k < n; ++k) {
		    int l1 = k + i;
		    if (l1 >= n) l1 -= n;
		    updata(f[nex][j][l1], f[cur][j][k]);
		    int l2 = k - i;
		    if (l2 < 0) l2 += n;
		    if (l1 == l2) continue;
		    updata(f[nex][j][l2], f[cur][j][k]);
		}
	    swap(cur, nex);
	}
	aa.n = I.n = n;
	I.a[0] = 1;
	for (int i = 0; i < n; ++i)
	    aa.a[i] = f[cur][0][i];
	c = power(d / n);
	d = d % n;
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; ++i) 
	    g[cur][i] = c.a[i];
	for (int i = 1; i <= d; ++i) {
	    memset(g[nex], 0, sizeof(g[nex]));
	    for (int j = 0; j < n; ++j) {
	    if (!g[cur][j]) continue;
		int l1 = j + i;
		if (l1 >= n) l1 -= n;
		//printf("%d %d %d\n", i, j, l);
		updata(g[nex][l1], g[cur][j]);
		int l2 = j - i;
		if (l2 < 0) l2 += n;
		if (l2 == l1) continue;
		//printf("%d %d %d\n", i, j, l);
		updata(g[nex][l2], g[cur][j]);
	    }
	    swap(cur, nex);
	}
	return g[cur][0];
    }
};