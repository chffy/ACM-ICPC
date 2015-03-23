#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stack>
using namespace std;

const int M = 2505;
const int N = 65;
int  tot;
pair<int, int> pre[M];
vector <int> edge1[N], edge2[N];
int father1[N], father2[N];
int first[N], Next[M * 2], End[M * 2], wi[M * 2];
 
void getfather(int x, int fa, int father[], vector<int> edge[]) {
    father[x] = fa;
    for (int i = 0; i < edge[x].size(); ++i) {
	int y = edge[x][i];
	if (y == fa) continue;
	getfather(y, x, father, edge);
    }
}

void addedge(int x, int y, int s) {
    Next[++tot] = first[x];
    first[x] = tot;
    End[tot] = y;
    wi[tot] = s;
}

void add(int x, int y, int s) {
    addedge(x, y, s);
    addedge(y, x, 0);
   // printf("%d %d %d\n", x, y, s);	
}

int S, T, h[N], num[N];

int maxflow(int x, int flow) {
    if (x == T) return flow;
    int ans = 0;
    for (int k = first[x]; ~k; k = Next[k])
	if (h[End[k]] + 1 == h[x] && wi[k]) {
	    int t = maxflow(End[k], min(flow - ans, wi[k]));
	   // printf("%d %d %d %d %d %d\n", x, flow, End[k], t, wi[k], ans + t);
	    ans += t;
	    wi[k] -= t;
	    wi[k ^ 1] += t;
	    if (ans == flow) return ans;
	}
    if (h[S] >= T + 1) return ans;
    --num[h[x]];
    if (num[h[x]] == 0) h[S] = T + 1;
    ++h[x];
    num[h[x]]++;
    return ans;
}

class DoubleTree {
public:
    int maximalScore(vector <int> a, vector <int> b, vector <int> c, vector <int> d, vector <int> score) {
	int n = a.size() + 1;
	for (int i = 0; i < n - 1; ++i) {
	    int x = a[i], y = b[i];
	    edge1[x].push_back(y);
	    edge1[y].push_back(x);
	    x = c[i], y = d[i];
	    edge2[x].push_back(y);
	    edge2[y].push_back(x);
	}
	int ans = 0;
	for (int root = 0; root < n; ++root) {
	    getfather(root, -1, father1, edge1);
	    getfather(root, -1, father2, edge2);
	    int edgetot = 0;
	    for (int i = 0; i < n; ++i) { 
		if (~father1[i]) 
		    pre[edgetot++] = make_pair(i, father1[i]);
		if (~father2[i])
		    pre[edgetot++] = make_pair(i, father2[i]);
	    }
	    S = n; T = S + 1;
	    memset(first, -1, sizeof(first));
	    tot = -1;
	    int sum = 0;
	    for (int i = 0; i < n; ++i) 
		if (score[i] > 0) add(S, i, score[i]), sum += score[i];
		else add(i, T, -score[i]);
	    for (int i = 0; i < edgetot; ++i)
		add(pre[i].first, pre[i].second, 1 << 30);
	    int flow = 0;
	    memset(num, 0, sizeof(num));
	    memset(h, 0, sizeof(h));
	    num[0] = T + 1;
	    while (h[S] < T + 1) flow += maxflow(S, 1 << 30);
	    ans = max(ans, sum - flow);
	}
	return ans;
    }
};
