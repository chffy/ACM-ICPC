#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct shop {
    int f, r, g, b;
    
    shop() {}
    
    int eend() {
	return f + r + g + b - 1;
    }

    shop(int _f, int _r, int _g, int _b):f(_f), r(_r), g(_g), b(_b) {}
    
    int operator < (const shop &a) const {
	return f < a.f;
    }
};

int bo[100];
typedef long long LL;
const int P = 1e9 + 7;

int f[505][105][105];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int d[505][505];

int C(int n, int m) {
    if (m > n) return 0;
    if (m == 0) return 1;
    if (d[n][m]) return d[n][m];
    d[n][m] = (C(n - 1, m - 1) + C(n - 1, m)) % P;
    return d[n][m];
}

int getnum(int r, int g, int b) {
    return (LL)C(r + g, g) * C(r + g + b, r + g) % P;
}

int dp(vector<shop> &C) {
    int tmin = C[0].f, tmax = C.back().eend();
    for (int i = tmin - 1; i <= tmax; ++i)
	memset(f[i], 0, sizeof(f[i]));
    if (C[0].r) f[tmin][1][0] = 1;
    if (C[0].g) f[tmin][0][1] = 1;
    if (C[0].b) f[tmin][0][0] = 1;
    int S = 0, n = C.size();
    for (int i = tmin; i < tmax; ++i) {
	for (int j = 0; j <= C[S].r; ++j)
	    for (int k = 0; k <= C[S].g; ++k)
		if (f[i][j][k]) {
		    int res = f[i][j][k];
		    int numr = C[S].r - j, numg = C[S].g - k;
		    int numb = C[S].b - (i - C[S].f + 1 - j - k);
		    if (S + 1 < n && C[S + 1].f == i + 1) {
			if (numr > C[S + 1].r || numg > C[S + 1].g || 
			    numb > C[S + 1].b) continue;
			int p = (LL)res * getnum(numr, numg, numb) % P;
			updata(f[i + numr + numg + numb][numr][numg], p);
		    }
		    else {
			if (numr) updata(f[i + 1][j + 1][k], res);
			if (numg) updata(f[i + 1][j][k + 1], res);
			if (numb) updata(f[i + 1][j][k], res);
		    }
		}
	    if (S + 1 < n && C[S + 1].f == i + 1) ++S;
    }
    return f[tmax][C.back().r][C.back().g];
}
 
class WinterAndShopping {
public:
    int getNumber(vector <int> f, vector <int> r, vector <int> g, vector <int> b) {
	int n = f.size();
	vector<shop> SH;
	for (int i = 0; i < n; ++i)
	    SH.push_back((shop) {f[i], r[i], g[i], b[i]});
	sort(SH.begin(), SH.end());
	memset(bo, 0, sizeof(bo));
	int ans = 1;
	for (int k = 0; k < n; ++k)
	for (int i = 0; i < n; ++i) {
	    int j;
	    if (bo[i]) continue;
	    for (j = 0; j < n; ++j)
		if (!bo[j] && i != j)
		    if (SH[i].f >= SH[j].f && SH[i].eend() <= SH[j].eend())
			break;
	    if (j >= n) continue;
	    if (SH[i].r > SH[j].r || SH[i].b > SH[j].b ||
		SH[i].g > SH[j].g) return 0;
	    ans = (LL)ans * getnum(SH[i].r, SH[i].g, SH[i].b) % P;
	    SH[j].r -= SH[i].r;
	    SH[j].g -= SH[i].g;
	    SH[j].b -= SH[i].b;
	    bo[i] = 1;
	    for (int j = 0; j < n; ++j)
		if (!bo[j] && SH[j].f > SH[i].eend())
		    SH[j].f -= SH[i].r + SH[i].g + SH[i].b; 
	}
	vector<shop> ST, C;
	for (int i = 0; i < SH.size(); ++i) 
	    if (!bo[i] && SH[i].eend() >= SH[i].f) ST.push_back(SH[i]);
	for (int i = 0; i < ST.size(); ++i) {
	    C.push_back(ST[i]);
	    if (i == ST.size() - 1 || ST[i].eend() < ST[i + 1].f) {
		ans = (LL)ans * dp(C) % P;
		C.clear();
	    }
	}
	return ans;
    }
};
