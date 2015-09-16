#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

const int N = 1e5 + 5;

int first[N], tot;
int m1[N], m2[N];

struct Edge {
    int y, nex;
}edge[N << 1];

int degree[N], bo[N];
int val[N], sum[N], f[N];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &val[i]);
        tot = 0;
        memset(first, -1, sizeof(first));
        memset(degree, 0, sizeof(degree));
        memset(bo, 0, sizeof(bo));
        for (int i = 1; i <= m; ++i) {
            int &x = m1[i], &y = m2[i];
            scanf("%d%d", &x, &y);
            addedge(x, y);
            addedge(y, x);
            ++degree[x];
            ++degree[y];
        }
        queue<int> que;
        for (int i = 1; i <= n; ++i)
            if (degree[i] < 2) {
                que.push(i);
                bo[i] = 1;
            }
        while (!que.empty()) {
            int x = que.front(); que.pop();
            for (int k = first[x]; k != -1; k = edge[k].nex)
                if (!bo[edge[k].y] && --degree[edge[k].y] < 2) {
                    bo[edge[k].y] = 1;
                    que.push(edge[k].y);
                }
        }
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            f[i] = i;
            sum[i] = 0;
        }
        for (int i = 1; i <= m; ++i)
            if (!bo[m1[i]] && !bo[m2[i]]) {
                f[find(m1[i])] = find(m2[i]);
            }
        for (int i = 1; i <= n; ++i)
            if (!bo[i]) sum[find(i)]++;
        for (int i = 1; i <= n; ++i)
            if (!bo[i] && (sum[find(i)] & 1)) ans = ans + val[i];
        printf("%I64d\n", ans);
    }
    return 0;
}
