#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int N = 2e5 + 5, M = 5e5 + 5;

int ans[N];
int sum[M], xx[N], yy[N], bo[M];
set<int> ver[M];
vector<int> edge, son[M];

void color(int id) {
    static int mark = 0;
    mark ^= 1;
    ans[id] = mark;
}

int degree[M];

int dfs(int x) {
    bo[x] = 1;
    while (!ver[x].empty()) {
        int id = *ver[x].begin();
        int y = xx[id];
        if (y == x) y = yy[id] + N;
        ver[x].erase(id);
        ver[y].erase(id);
        if (bo[y]) {
            color(id);
            bo[x] = 0;
            return y;
        }
        int tmp = dfs(y);
        if (tmp == -1) {
            son[x].push_back(id);
            ++degree[y];
        }
        else {
            color(id);
            if (tmp != x) {
                bo[x] = 0;
                return tmp;
            }
        }
    } 
    bo[x] = 0;
    return -1;
}

void solve(int x) {
    for (int i = 0; i < son[x].size(); ++i) {
        int id = son[x][i];
        int y = xx[id];
        if (y == x) y = yy[id] + N;
        if (sum[x] > 0) {
            ans[id] = 1;
            --sum[x];
            --sum[y];
        }
        else {
            ++sum[x];
            ++sum[y];
        }
        solve(y);
    }
    son[x].clear();
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &xx[i], &yy[i]);
        ver[xx[i]].insert(i);
        ver[yy[i] + N].insert(i);
    }
    for (int i = 1; i < M; ++i) {
        dfs(i);
    }
    memset(bo, 0, sizeof(bo));
    for (int i = 1; i < M; ++i)
        if (degree[i] == 0) {
            solve(i);
        }
    for (int i = 1; i <= n; ++i)
        printf("%c", "br"[ans[i]]);
    puts("");
    return 0;
}
