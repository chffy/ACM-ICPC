#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

bool f[55][55];
int parent[55], size_n[55],size_m[55] ;

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

int dp[55];
int n;

int dfs(int x) {
    if (dp[x]) return dp[x];
    int &ans = dp[x];
    ans = 0;
    for (int j = 0; j < n; ++j)
	if (j != x && find(j) == j &&
	    f[j][x] && size_n[j] > 1) ans = max(ans, dfs(j));
    return ans = ans + 1;
}

class BigO {
public:
    int minK(vector <string> graph) {
	n = graph.size();
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < n; ++j)
		f[i][j] = (graph[i][j] == 'Y');
	for (int i = 0; i < n; ++i)
	    graph[i][i] = 1;
	for (int k = 0; k < n; ++k)
	    for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		    f[i][j] |= f[i][k] & f[k][j];
	for (int i = 0; i < n; ++i)
	    parent[i] = i;
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < n; ++j)
		if (f[i][j] && f[j][i])
		    parent[find(i)] = find(j);
	for (int i = 0; i < n; ++i) 
	    for (int j = 0; j < n; ++j)
		if (graph[i][j] == 'Y' && find(i) == find(j))
		    ++size_m[find(i)];
	for (int i = 0; i < n; ++i)
	    ++size_n[find(i)];
	for (int i = 0; i < n; ++i)
	    if (size_m[find(i)] != size_n[find(i)] && size_n[find(i)] != 1) {
	    	return -1;
	    }
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < n; ++i)
	    if (find(i) == i && size_n[i] > 1)
		dfs(i);
	int ans = 1;
	for (int i = 0; i < n; ++i)
	    ans = max(ans, dp[i]);
	return ans - 1;
    }
};