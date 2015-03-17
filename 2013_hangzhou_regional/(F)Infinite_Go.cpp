#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int N = 1e4 + 5;

map<pair<int, int>, int> ext;
set<pair<int, int> > vis[N];

int f[N], n, sum[N];
int C[4] = {1, -1, 0, 0};
int D[4] = {0, 0, 1, -1};

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

void union_f(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return ;
    if (vis[tx].size() < vis[ty].size()) swap(tx, ty);
    while (!vis[ty].empty()) {
        vis[tx].insert(*vis[ty].begin());
        vis[ty].erase(*vis[ty].begin());
    }
    f[ty] = tx;
    sum[tx] += sum[ty];
    sum[ty] = 0;
}

void del(int x) {
    x = find(x);
    for (set<pair<int, int> >::iterator it = vis[x].begin();
         it != vis[x].end(); ++it) {
        for (int k = 0; k < 4; ++k) {
            int xx = it -> first + C[k], yy = it -> second + D[k];
            pair<int, int> tmp = make_pair(xx, yy);
            if (!ext.count(tmp)) {
                //puts("error");
                continue;
            }
            if (find(ext[tmp]) != find(x)) 
                ++sum[find(ext[tmp])];
        }
    }
    for (set<pair<int, int> >::iterator it = vis[x].begin();
         it != vis[x].end(); ++it) {
        ext.erase(make_pair(it -> first, it -> second));
    }
    vis[x].clear();
}

void add(int x, int y, int i) {
    vis[i].clear();
    f[i] = i;
    sum[i] = 0;
    vis[i].insert(make_pair(x, y));
    ext[make_pair(x, y)] = i;
    int p = 0;
    for (int k = 0; k < 4; ++k) {
        int xx = x + C[k], yy = y + D[k];
        pair<int, int> tmp = make_pair(xx, yy);
        if (!ext.count(tmp)) {
            if (tmp.first > 0 && tmp.second > 0)
                ++p;
        }
        else if ((ext[tmp] & 1) == (i & 1)) {
            sum[find(ext[tmp])]--;
            union_f(ext[tmp], i);
        }
        else {
            --sum[find(ext[tmp])];
            if (sum[find(ext[tmp])] == 0)
                del(ext[tmp]);
        }
    }
    sum[find(i)] += p;
    if (sum[find(i)] == 0) del(i);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        ext.clear();
        for (int i = 1; i <= n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x, y, i);
        }
        int ans[2] = {0, 0};
        for (int i = 1; i <= n; ++i)
            ans[i & 1] += vis[i].size();
        printf("%d %d\n", ans[1], ans[0]);
    }
    return 0;
}