#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 55;
int a[N], n, bo[N], vis[N];
int degree[N];
vector<int> son[N];

int dfs(int mark, int dep = 1) {
    pair<int, int> K = make_pair(1 << 30, -1);
    for (int i = 0; i < n; ++i)
        if (bo[i] == mark && !vis[i]) {
            int de = 0;
            for (int j = 0; j < son[i].size(); ++j) {
                int y = son[i][j];
                if (bo[y] == mark && !vis[y]) ++de;
            }
            K = min(make_pair(de, i), K);
        }
    if (K.second == -1) return 0;
    vector<int> Ni;
    Ni.push_back(K.second);
    for (int i = 0; i < son[K.second].size(); ++i) {
        int y = son[K.second][i];
        if (bo[y] == mark && !vis[y]) {
            Ni.push_back(y);
        }
    }
    int ans = 0;
    for (int i = 0; i < Ni.size(); ++i) {
        int x = Ni[i];
        for (int j = 0; j < son[x].size(); ++j) { 
            int y = son[x][j];
            if (!vis[y]) {
                vis[y] = dep;
            }
        }
        vis[x] = dep;
        ans = max(dfs(mark, dep + 1) + 1, ans);
        vis[x] = 0;
        for (int j = 0; j < son[x].size(); ++j) {
            int y = son[x][j];
            if (vis[y] == dep) {
                vis[y] = 0;
            }
        }
    }
    return ans;
}

class GearsDiv1 {
public:
    int getmin(string color, vector <string> graph) {
        n = color.size();
        for (int i = 0; i < n; ++i) {
            if (color[i] == 'R') a[i] = 0;
            if (color[i] == 'G') a[i] = 1;
            if (color[i] == 'B') a[i] = 2;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (graph[i][j] == 'Y') son[i].push_back(j);
        for (int mask = 0; mask < 1 << 3; ++mask) {
            memset(degree, 0, sizeof(degree));
            memset(vis, 0, sizeof(vis));
            for (int i = 0; i < n; ++i)
                if (mask >> a[i] & 1) bo[i] = 1;
                else bo[i] = 0;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < son[i].size(); ++j)
                    if (bo[i] == bo[son[i][j]]) ++degree[i];
            ans = max(dfs(1) + dfs(0), ans);
        }
        return n - ans;
    }
};
