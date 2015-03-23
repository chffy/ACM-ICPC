#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
    int x, y, w;
    
    int operator < (const Edge &a) const {
	return w < a.w;
    }
}edge[405];

int parent[105];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

class ChristmasTreeDecoration {
public:
    int solve(vector <int> col, vector <int> x, vector <int> y) {
	int n = col.size(), m = x.size();
	for (int i = 0; i < m; ++i) {
	    edge[i].x = x[i];
	    edge[i].y = y[i];
	    edge[i].w = (col[x[i] - 1] == col[y[i] - 1]);
	}
	sort(edge, edge + m);
	for (int i = 1; i <= n; ++i) parent[i] = i;
	int ans = 0;
	for (int i = 0; i < m; ++i) 
	    if (find(edge[i].x) != find(edge[i].y)) {
		parent[find(edge[i].x)] = find(edge[i].y);
		ans += edge[i].w;
	    }
	return ans;
    }
};