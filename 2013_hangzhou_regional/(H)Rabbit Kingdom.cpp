#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5 + 5;
vector<int> pri[N];
int bo[N], position[N], a[N];
int n, m, ans[N];

struct Event {
    int ll, rr, id;
}event[N];

vector<pair<int, int> > eve[N];

struct Que {
    int l, r, id;

    int operator < (const Que &a) const {
        return l < a.l;
    }
}que[N];

int f[N], g[N];

void add(int x, int s, int f[]) {
    while (x <= n) {
        f[x] += s;
        x += x & -x;
    }
}

int find(int x, int f[]) {
    int ans = 0;
    while (x > 0) {
        ans += f[x];
        x -= x & -x;
    }
    return ans;
}

void work() {
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]), event[i].id = i;
    for (int i = 2; i < N; ++i) position[i] = 0;
    for (int i = 1; i <= n; ++i) {
        int &ret = event[i].ll;
        ret = 1;
        int x = a[i];
        for (int j = 0; j < pri[x].size(); ++j) {
            ret = max(ret, position[pri[x][j]] + 1);
            position[pri[x][j]] = i;
        }
    }
    for (int i = 1; i < N; ++i) position[i] = n + 1;
    for (int i = n; i > 0; --i) {
        int &ret = event[i].rr;
        ret = n;
        int x = a[i];
        for (int j = 0; j < pri[x].size(); ++j) {
            ret = min(ret, position[pri[x][j]] - 1);
            position[pri[x][j]] = i;
        }
    }
    for (int i = 1; i <= n + 1; ++i)
        eve[i].clear();
    for (int i = 1; i <= n; ++i) {
        eve[event[i].ll].push_back(make_pair(event[i].rr, event[i].id));
        eve[event[i].id + 1].push_back(make_pair(-event[i].rr, event[i].id));
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que + 1, que + 1 + m);
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    for (int i = 1, j = 1; i <= n; ++i) {
        for (int k = 0; k < eve[i].size(); ++k) {
            int r = eve[i][k].first;
            int id = eve[i][k].second;
            if (r < 0) add(-r, -1, f);
            else add(r, 1, f);
            if (id < 0) add(-id, -1, g);
            else add(id, 1, g);
        }
        while (j <= m && que[j].l == i) {
            //printf("%d %d\n", i, j);
            ans[que[j].id] = find(n, f) - find(que[j].r - 1, f);
            ans[que[j].id] -= find(n, g) - find(que[j].r, g);
            ++j;
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
}

int main() {
    int ans = 0;
    for (int i = 2; i < N; ++i)
        if (!bo[i]) {
            for (int j = i; j < N; j += i) {
                bo[j] = 1;
                pri[j].push_back(i);
            }
        }
    while (scanf("%d%d", &n, &m), n || m)
        work();
    return 0;
}