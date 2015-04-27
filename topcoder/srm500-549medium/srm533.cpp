#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int f[101][101], g[101][101];
int N, tot;

void dfs(int x) {
    for (int i = 1; i <= N; ++i)
	if (g[x][i]) {
	    --g[x][i];
	    --g[i][x];
	    ++tot;
	    dfs(i);
	}
}

int degree[101];

class MagicBoard {
public:
    string ableToUnlock(vector <string> board) {
	int n = board.size();
	int m = board[0].size();
	int sum = 0;
	N = n + m;
	for (int i = 1; i <= n; ++i)
	    for (int j = 1; j <= m; ++j) 
		if (board[i - 1][j - 1] == '#') {
		    ++sum;
		    int p = i, q = n + j;
		    f[p][q] = f[q][p] = 1;
		    ++degree[p];
		    ++degree[q];
		}
	int p = 0, source = 0;
	for (int i = 1; i <= n + m; ++i)
		if (degree[i] & 1) ++p, source = i;
	if (p) {
	    if (p != 2 || source <= n) return "NO";
	}
	else {
		for (int i = n + 1; i <= n + m; ++i)
			if (degree[i]) source = i;
	}
	memcpy(g, f, sizeof(g));
	if (source) dfs(source);
	if (tot == sum) return "YES";
	return "NO";
    }
};
