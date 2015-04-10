#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
int n, tot;
int first[100], Next[200], End[200];
LL f[51][3];
int maxdep;
int flag = 0;

void add_edge(int x, int y) {
    Next[++tot] = first[x];
    first[x] = tot;
    End[tot] = y;
}

void dfs(int x, int fa, int Dep) {
    if (flag) return ;
    int num = 0, L = -1, R = -1;
    for (int k = first[x]; k; k =Next[k]) {
	int l = End[k];
	if (l == fa) continue;
	dfs(l, x, Dep + 1); 
	++num;
	if (L == -1) L = l;
	else R = l;
    }
    if (flag) return ;
    if (num > 2) {
	flag = 1;
	return;
    }
    if (num == 0) {
	if (Dep > maxdep || Dep < maxdep - 1) {
	    flag = 1;
	    return;
	}
	if (Dep == maxdep) f[x][0] = 1;
	else f[x][2] = 1;
	//return ;
    }
    if (num == 1 && Dep != maxdep - 1) {
	flag = 1;
	return ;
    }
    if (num == 2) f[x][0] = f[L][0] * f[R][0] * 2;
    if (num == 2) f[x][1] = f[L][0] * (f[R][1] + f[R][2]) + f[R][0] * (f[L][1] + f[L][2]) + f[L][1] * f[R][2] + f[R][1] * f[L][2];
    if (num == 2) f[x][2] = f[L][2] * f[R][2] * 2;
    if (num == 1) f[x][1] = f[L][0];
    //printf("%d %lld %lld %lld\n", x, f[x][0], f[x][1],f[x][2]);
}

class HatRack {
public:
    LL countWays(vector <int> knob1, vector <int> knob2) {
	tot = 0;
	n = knob1.size() + 1;
	for (int i = 0; i < n - 1; ++i) {
	    int x = knob1[i], y= knob2[i];
	    add_edge(x, y);
	    add_edge(y, x);
	}
	for (int i = 0, j = 0; ; ++i) {
	    j += 1 << i;
	    maxdep = i;
	    if (j >= n) break;
	}
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
	    memset(f, 0, sizeof(f));
	    flag = 0;
	    dfs(i, 0, 0);
	    //	if (i == 4) cout << flag << endl;
	    if (flag) continue;
	    ans += f[i][1] + f[i][0] + f[i][2];
	} 
	return ans;
    }
};
