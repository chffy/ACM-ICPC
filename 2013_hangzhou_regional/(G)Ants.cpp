#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
#include <iostream>
#include <bitset>
using namespace std;

const int N = 1e5 + 5;
typedef long long LL;

struct Edge {
    int y, nex;
    LL s;
}edge[N * 2];

int first[N], tot, n, m;
LL value[N], P[N * 61];
bitset<62> val[N];
int f[N * 61][2], sum[N * 61], mark[N], fa[N * 61];

void addedge(int x, int y, LL s) {
    edge[tot] = (Edge) {y, first[x], s};
    first[x] = tot++;
}

void dfs(int x, int fa, LL s) {
    value[x] = s;
    for (int k = first[x]; ~k; k = edge[k].nex)
        if (edge[k].y != fa)
            dfs(edge[k].y, x, s ^ edge[k].s);
}

void build(int x, int i, int p) {
    if (p < 0) {
        ++sum[x];
        P[x] = value[i];
        return ;
    }
    int y, bi = val[i][p];
    if (~f[x][bi]) y = f[x][bi];
    else {
        y = f[x][bi] = ++tot;
        fa[tot] = x;
        f[tot][0] = f[tot][1] = -1;
        sum[tot] = 0;
    }
    build(y, i, p - 1);
}

struct PATH {
    int fr, ed, num;
    LL val;

    int operator < (const PATH &a) const {
        return val < a.val;
    }
};

priority_queue<PATH> que;
LL ans[N * 2];

int gett(int fr, int x) {
    int s = fa[x], T = 60;
    //cout << sum[x] << endl;
    if (sum[x]) {
        s = x;
        T = 0;
        x = fa[x];
    }
    while (!sum[x]) {
        if (x == -1) return -1;
        int bi = val[fr][T] ^ 1;
        if (s == fa[x] && ~f[x][bi]) {
            s = x;
            x = f[x][bi];
            --T;
        }
        else if ((s == f[x][bi] || (s == fa[x] && f[x][bi] == -1)) && ~f[x][bi ^ 1]) {
            s = x;
            x = f[x][bi ^ 1];
            --T;
        }
        else {
            s = x;
            x = fa[x];
            ++T;
        }
    }
    return x;
}

void solve() {
    m = 200000;
    if (n < 1000)
        m = min(m, n * (n - 1));
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; ++i) {
        int c = gett(i, 0);
        if (c == -1) continue;
        que.push((PATH){i, c, sum[c], value[i] ^ P[c]});
    }
    for (int i = 1; i <= m; ++i) {
        PATH pa = que.top(); que.pop();
       // printf("%d %d %lld\n", pa.fr, pa.ed, pa.val);
        --pa.num;
        ans[i] = pa.val;
        if (pa.num == 0) {
            int x = pa.fr, s = pa.ed;
            int c = gett(x, s);
            if (c == -1) continue;
            que.push((PATH){x, c, sum[c], value[x] ^ P[c]});
            //printf("%lld %lld\n", a.val, value[])
        }
        else que.push(pa);
    }
}

int main() {
    while (scanf("%d", &n), n) {
        memset(first, -1, sizeof(first));
        tot = 0;
        for (int i = 1; i < n; ++i) {
            int x, y;
            LL s;
            scanf("%d%d%lld", &x, &y, &s);
            addedge(x, y, s);
            addedge(y, x, s);
        }
        dfs(1, 0, 0);
        tot = 0;
        sum[0] = 0;
        //memset(f, -1, sizeof(f));
        memset(f, -1, sizeof(f));
        memset(sum, 0, sizeof(sum));
        memset(fa, 0, sizeof(fa));
        f[0][0] = f[0][1] = -1;
        fa[0] = -1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= 60; ++j)
                if (value[i] >> j & 1) val[i][j] = 1;
                else val[i][j] = 0;
            build(0, i, 60);
        }
        solve();
        int q;
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i) {
            int k;
            scanf("%d", &k);
            if (k > m) puts("-1");
            else printf("%lld\n", ans[k]);
        }
    }
    return 0;
}