#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

struct Edge {
    int x, y, s;

    int operator < (const Edge &A) const {
        return s < A.s;
    }
}edge[N];

pair<int, int> pr[N];
int f[N], sum[N];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

typedef long long LL;

LL ans[N];

LL calc(LL x) {
    return x * (x - 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].s);
        }
        sort(edge + 1, edge + 1 + m);
        for (int i = 1; i <= q; ++i) {
            scanf("%d", &pr[i].first);
            pr[i].second = i;
        }
        sort(pr + 1, pr + 1 + q);
        for (int i = 1; i <= n; ++i)
            f[i] = i, sum[i] = 1;
        LL res = 0;
        for (int i = 1, j = 1; i <= q; ++i) {
            while (j <= m && edge[j].s <= pr[i].first) {
                int x = edge[j].x, y = edge[j].y;
                if (find(x) != find(y)) {
                    res -= calc(sum[find(x)]) + calc(sum[find(y)]);
                    sum[find(x)] += sum[find(y)];
                    res += calc(sum[find(x)]);
                    f[find(y)] = find(x);
                }
                ++j;
            }
            ans[pr[i].second] = res;
        }
        for (int i = 1; i <= q; ++i)
            printf("%I64d\n", ans[i]);
    }
    return 0;
}
