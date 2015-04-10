#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int a[51][51];
int n, m;
const int p = 1e9 + 7;

int f[51][51];

void check(int &l, int &r, int line) {
    for (int i = 1; i <= m; ++i){
	if (a[line][i] == 1) l = max(l, i);
	if (a[line][i] == 2) r = min(i - 1, r);
    }
}

int dp() {
    memset(f, 0, sizeof(f));
    int ans = 0;
    int l = 1, r = m;
    check(l, r, 1);
    for (int i = l; i <= r; ++i) f[1][i] = 1;
    for (int i = 2; i <= n; ++i) {
	int l = 0, r = m, ans = 0;
	check(l, r, i);
	for (int j = m; j >= 0; --j) {
	    ans += f[i - 1][j];
	    ans %= p;
	    if (j >= l && j <= r) f[i][j] = ans;
	}
    }
    for (int i = 0; i <= m; ++i) {
	ans += f[n][i];
	ans %= p;
    }
    memset(f, 0, sizeof(f));
    l = 1, r = m;
    check(l, r, n);
    for (int i = l; i <= r; ++i) f[n][i] = 1;
    for (int i = n - 1; i; --i) {
	int l = 0, r = m, ans = 0;
	check(l, r, i);
	//printf("%d %d %d\n", l, r, i);
	for (int j = m; j >= 0; --j) {
	    ans += f[i + 1][j];
	    ans %= p;
	    if (j >= l && j <= r) f[i][j] = ans;
	}
    }
    for (int i = 0; i <= m; ++i) {
	ans += f[1][i];
	ans %= p;
    }
    for (int i = 1; i <= m; ++i) {
	int flag = 0;
	for (int j = 1; j <= n; ++j)
	    for (int k = 1; k <= i; ++k)
		if (a[j][k] == 2) flag = 1;
	if (flag) continue;
	for (int j = 1; j <= n; ++j)
	    for (int k = i + 1; k <= m; ++k)
		if (a[j][k] == 1) flag = 1;
	if (flag) continue;
	if (--ans < 0) ans += p;
    }
    return ans;
}

class TwoConvexShapes {
public:
    int countWays(vector <string> grid) {
	n = grid.size(), m = grid[0].size();
	for (int i = 1; i <= n; ++i) 
	    for (int j = 1; j <= m; ++j) {
		if (grid[i - 1][j - 1] == 'B') a[i][j] = 1;
		if (grid[i - 1][j - 1] == 'W') a[i][j] = 2;
		if (grid[i - 1][j - 1] == '.') a[i][j] = 0;
	    }
	int ans = 0;
	ans += dp();
	ans %= p;
	for (int i = 1; i <= n; ++i)
	    for (int j = 1; j <= m; ++j) {
		if (a[i][j] == 1) a[i][j] = 2;
		else if (a[i][j] == 2) a[i][j] = 1;
	    }
	ans +=dp();
	ans %= p;
	for (int i = 1; i < n; ++i) {
	    int flag1 = 1, flag2 = 1;
	    for (int j = 1; j <= i; ++j)
		for (int k = 1; k <= m; ++k) {
		    if (a[j][k] == 1) flag1 = 0;
		    if (a[j][k] == 2) flag2 = 0;
		}
	    for (int j = i + 1; j <= n; ++j)
		for (int k = 1; k <= m; ++k) {
		    if (a[j][k] == 2) flag1 = 0;
		    if (a[j][k] == 1) flag2 = 0;
		}
	    ans -= flag1 + flag2;
	    if (ans < 0) ans += p;
	}
	return ans;
    }
};
