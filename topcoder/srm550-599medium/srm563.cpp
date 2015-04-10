#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int le[1000], a[1000];
int da[1000], b[1000];
int f[101][51];

class SpellCards {
public:
    int maxDamage(vector <int> level, vector <int> damage) {
	int n = level.size();
	for (int i = 1; i <= 2 * n; ++i) { 
	    int j = i;
	    if (j > n) j -= n;
	    le[i] = level[j - 1];
	    da[i] = damage[j - 1];
	}
	int ans = 0;
	for (int I = 1; I <= n; ++I) {
	    memset(f, -1, sizeof(f));
	    for (int i = 1; i <= n; ++i)
		a[i] = le[i + I - 1], b[i] = da[i + I - 1];
	    f[n + 1][0] = 0;
	    for (int i = n; i; --i)
		for (int j = 0; j <= n; ++j) {
		    if (j && ~f[i + 1][j - 1])
			f[i][j] = max(f[i][j], f[i + 1][j - 1]);
		    if (j + a[i] - 1 <= n && ~f[i + 1][j + a[i] - 1])
			f[i][j] = max(f[i][j], f[i + 1][j + a[i] - 1] + b[i]);
		}
	    for (int i = 0; i <= n; ++i) {
		ans = max(ans, f[1][i]);
		//printf("%d %d %d %d\n", I, i, f[1][i], a[i]);
            }
	}
	return ans;
    }
};
