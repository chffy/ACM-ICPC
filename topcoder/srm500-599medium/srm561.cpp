#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

const int N = 55;
int incircle[N][N];
int bo[N], a[N];
int first[N], Next[N * 2], End[N * 2];
int tot, degree[N];

void addedge(int x, int y) {
    Next[++tot] = first[x];
    first[x] = tot;
    End[tot] = y;
   // printf("%d %d\n", x, y);
}

int sqr(int x) {
    return x * x;
}

int getlen(int x, int y) {
    return sqr(x) + sqr(y);
}

int f[55];

set<int> ext;

void search(int x, int mark) {
    for (int k = first[x]; k; k = Next[k]) 
	mark ^= f[End[k]];
    ext.insert(mark);
    for (int k = first[x]; k; k = Next[k])
	search(End[k], mark ^ f[End[k]]);
}

void dfs(int x) {
    for (int k = first[x]; k; k = Next[k]) 
	dfs(End[k]);
    ext.clear();
    search(x, 0);
    for (int i = 0; ; ++i)
	if (!ext.count(i)) {
	    f[x] = i;
	    break;
	}
}
 
class CirclesGame {
public:
    string whoCanWin(vector <int> x, vector <int> y, vector <int> r) {
	int n = x.size(), m = 0;
	memset(bo, 0, sizeof(bo));
	memset(first, 0, sizeof(first));
	memset(degree, 0, sizeof(degree));
	tot = 0;
	for (int i = 0; i < n; ++i) {
	    int j;
	    for (j = 0; j < n; ++j) {
	    if (bo[j]) continue;
		int k;
		for (k = 0; k < n; ++k)
		    if (!bo[k] && (r[k] > r[j]) &&
			(getlen(x[k] - x[j], y[k] - y[j]) < sqr(r[k])))
			break;
		if (k >= n) break;
	    }
	    assert(j < n);
	    int k = -1;
	    for (int l = 0; l < m; ++l)
		if (r[a[l]] > r[j] && 
		    getlen(x[a[l]] - x[j], y[a[l]] - y[j]) < sqr(r[a[l]]))
		    k = a[l];
	    if (~k) addedge(k, j), ++degree[j];
	    bo[j] = 1;
	    a[m++] = j;
	}
	int ans = 0;
	memset(f, 0, sizeof(f));
	for (int i = 0; i < n; ++i)
	    if (!degree[i]) {
		dfs(i);
		ans ^= f[i];
	    }
	if (ans) return "Alice";
	else return "Bob";
    }
};
