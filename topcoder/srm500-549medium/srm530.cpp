#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

bool vis[51][51], bo[51], mark[51];
int pre[51], dis[51];

queue <int> que;
int n;

int spfa(const vector<string> edge) {
    memset(dis, 63, sizeof(dis));
    memset(bo, false, sizeof(bo));
    dis[0] = 0;
    que.push(0);
    while (!que.empty()) {
	int x = que.front();  que.pop();
	bo[x] = false;
	for (int i = 0; i < n; ++i)
	    if (edge[x][i] == 'Y' && dis[i] > dis[x] + 1) {
		dis[i] = dis[x] + 1;
		pre[i] = x;
		if (!bo[i]) {
		    bo[i] = true;
		    que.push(i);
		}
	    }
    }
    if (dis[n - 1] > 1000) return 0;
    mark[0] = true;
    for (int x = n - 1; x != 0; x = pre[x]) {
	mark[x] = true;
	vis[pre[x]][x] = true;
    }
    return 1;
}

bool dfs(int x, const vector<string> &edge, int dep) {
    if (mark[x]) return true;
    if (dep <= 0) return false;
    bo[x] = true;
    for (int i = 0; i < n; ++i)
	if (edge[x][i] == 'Y' && !bo[i])
	    if (dfs(i, edge, dep - 1)) {
		vis[x][i] = true;
		mark[x] = true;
		return true;
	    }
    return false;
}

class GogoXMarisaKirisima {
public:
    int solve(vector <string> edge) {
	n = edge.size();
	memset(vis, false, sizeof(vis));
	memset(mark, false, sizeof(mark));
	int ans = spfa(edge);
	while (1) {
	    int flag = 0; 
	    for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i)
		    if (mark[i])
		    for (int j = 0; j < n; ++j)
			if (edge[i][j] == 'Y' && !vis[i][j]) {
			    memset(bo, false, sizeof(bo));
			    if (dfs(j, edge, k)) {
				vis[i][j] = true;
				++ans;
				flag = 1;
			    }
			}
		if (flag) break;
	    }
	    if (!flag) break;
	}
	return ans;
    }
};
