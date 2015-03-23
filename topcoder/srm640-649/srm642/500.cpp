#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

const int N = 1e5 + 5;

int first[N], bo[N], S, T, Next[N * 4], End[N * 4], w1[N * 4], w2[N * 4];
int tot;
pair<int, int> de[30000];

void addedge(int x, int y, int s1, int s2) {
    Next[++tot] = first[x];
    first[x] = tot;
    End[tot] = y;
    w1[tot] = s1;
    w2[tot] = s2;
}

void add1(int x, int y, int s1, int s2) {
    addedge(x, y, s1, s2);
    addedge(y, x, 0, -s2);
}

vector<pair<int, int> > edge;
 
int dis[N], pre[N], prd[N], flow[N];

queue<int> que;

int check(int &ans) {
    for (int i = 0; i <= T; ++i) {
	dis[i] = 1 << 30;
	flow[i] = 0;
	bo[i] = 0;
    }
    flow[S] = 1 << 30; dis[S] = 0;
    que.push(S);
    while (!que.empty()) {
	int x = que.front(); que.pop();
	bo[x] = 0;
	for (int k = first[x]; ~k; k = Next[k]) 
	    if (w1[k] && dis[End[k]] > dis[x] + w2[k]) {
		dis[End[k]] = dis[x] + w2[k];
		flow[End[k]] = min(flow[x], w1[k]);
		pre[End[k]] = x;
		prd[End[k]] = k;
		if (!bo[End[k]])
		    que.push(End[k]), bo[End[k]] = 1;
	    }
    }
    if (!flow[T]) return 0;
    ans += flow[T] * dis[T];
    for (int x = T; x != S; x = pre[x]) {
	w1[prd[x]] -= flow[T];
	w1[prd[x] ^ 1] += flow[T];
    }
    return 1;
}

int minvalue() {
    int ans = 0;
    while (check(ans));
    return ans;
}

class TaroCutting {
public:
    int getNumber(vector <int> height, vector <int> add, vector <int> device, int time) {
	int n = height.size(), m = 0;
	sort(device.begin(), device.end());
	for (int i = time; i > 0; --i)
	    for (int j = 0; j < device.size(); ++j) 
		de[m++] = make_pair(j, i);
	sort(de, de + m);
	m = unique(de, de + m) - de;
	while (m < n) de[m++] = make_pair(-1, -1);
	S = n + m, T = S + 1;
	tot = -1;
	memset(first, -1, sizeof(first));
	for (int i = 0; i < m; ++i) 
	    add1(i + n, T, 1, 0);
	for (int i = 0; i < n; ++i)
	    add1(S, i, 1, 0);
	for (int i = 0; i < n; ++i) {
	    edge.clear();
	    for (int j = 0; j < m; ++j) {
		int p = device[de[j].first];
		if (de[j].first == -1) 
		    edge.push_back(make_pair(height[i] + time * add[i], j));
		else 
		    edge.push_back(make_pair(min(height[i] + time * add[i], p + add[i] * (time - de[j].second)), j));
	    }
	    sort(edge.begin(), edge.end());
	    for (int j = 0; j < edge.size() && j < n; ++j)
		add1(i, edge[j].second + n, 1, edge[j].first);
	}
	return minvalue();
    }
};
