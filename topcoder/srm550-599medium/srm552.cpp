#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int bo1[1801], bo2[1801];
int n, m;
int a[31][31], b[31][31];
int M;
int ZERO = 900;

void calc(int x1, int y1, int x2, int y2, int bo[]){
    for (int l1 = x1; l1 <= x2; ++l1)
	for (int r1 = y1; r1 <= y2; ++r1)
	    for (int l2 = l1; l2 <= x2; ++l2)
		for (int r2 = r1; r2 <= y2; ++r2) {
		    int t = a[l2][r2] - a[l1 - 1][r2] - a[l2][r1 - 1] + a[l1 - 1][r1 - 1];
		    int z = b[l2][r2] - b[l1 - 1][r2] - b[l2][r1 - 1] + b[l1 - 1][r1 - 1];
		    bo[t + ZERO] = max(bo[t + ZERO], z + 1);
		}
}

int solve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    memset(bo1, 0, sizeof(bo1));
    memset(bo2, 0, sizeof(bo2));
    calc(x1, y1, x2, y2, bo1);
    calc(x3, y3, x4, y4, bo2);
    int ans = -1;
    for (int i = - n * m; i <= n * m; ++i){
	if (!bo1[i + ZERO]) continue;
	for (int j = max(- n * m,  - i - M); j <= min(n * m, - i + M); ++j){
	    if (!bo2[j + ZERO]) continue;
	    ans = max(ans, bo1[i + ZERO] + bo2[j + ZERO] - 2);
	    //if (ans == 9) printf("%d %d\n", i, j);
	}
    }
    return ans;
}

class FoxAndFlowerShopDivOne{
public:
    int theMaxFlowers(vector <string> flowers, int maxDiff){
	n = flowers.size(), m = flowers[0].size();
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < m; ++j){
		if (flowers[i][j] == 'L') a[i + 1][j + 1] = -1;
		else if (flowers[i][j] == 'P') a[i + 1][j + 1] = 1;
		else a[i + 1][j + 1] = 0;
		b[i + 1][j + 1] = (a[i + 1][j + 1] != 0);
	    }
	for (int i = 1; i <=n; ++i)
	    for (int j = 0; j <=m; ++j){
		a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
	    }
	M = maxDiff;
	int ans = -1;
	for (int i = 2; i <= n; ++i)
	    ans = max(ans, solve(1, 1, i - 1, m, i, 1, n, m));
	for (int i = 2; i <= m; ++i)
	    ans = max(ans, solve(1, 1, n, i - 1, 1, i, n, m));
	return ans;
    }
};
