#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

int a[2][205];
int f[205][205][3];

void updata(int l, int r) {
    f[l][r][2] = min(f[l][r][2], f[l][r][0] + f[l][r][1]);
    f[l][r][2] = min(f[l][r][2], min(f[l][r][0], f[l][r][1]) + 1);
    f[l][r][0] = min(f[l][r][0], f[l][r][2]);
    f[l][r][1] = min(f[l][r][1], f[l][r][2]);
}

void solve(int mark, int l, int r, int ki, int kj) {
    for (int k = l; k < r; ++k)
	f[l][r][mark] = min(f[l][r][mark], f[l][k][mark] + f[k + 1][r][mark]);
    f[l][r][mark] = min(f[l][r][mark], f[l + 1][r][mark] + ki);
    f[l][r][mark] = min(f[l][r][mark], f[l][r - 1][mark] + kj);
}

class TheKingsArmyDiv1 {
public:
    int getNumber(vector <string> state) {
	int n = state[0].size();
	for (int i = 0; i < 2; ++i)
	    for (int j = 1; j <= n; ++j)
		a[i][j] = (state[i][j - 1] == 'S');
	memset(f, 63, sizeof(f));
	for (int i = 1; i <= n; ++i) {
	    if (!a[0][i]) f[i][i][0] = 0;
	    if (!a[1][i]) f[i][i][1] = 0;
	    updata(i, i);
	}
	for (int j = 2; j <= n; ++j)
	    for (int i = j - 1; i > 0; --i) {
		solve(0, i, j, a[0][i], a[0][j]);
		solve(1, i, j, a[1][i], a[1][j]);
		solve(2, i, j, a[0][i] | a[1][i], a[0][j] | a[1][j]);
		updata(i, j);
	    }
	if (f[1][n][2] > 10000000) return -1;
	else return f[1][n][2];
    }
};
