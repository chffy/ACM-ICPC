#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long LL;
int n, m, K;
int si[105], ti[105];
int ci[105][105], di[105][105];
int ei[105][105], fi[105][105], tot;
int first[405];

struct Edge {
    int y, nex;
    LL w1, w2;
}edge[1000000];

void addedge(int x, int y, LL s1, LL s2) {
    edge[tot] = (Edge) {y, first[x], s1, s2};
    first[x] = tot++;
}

void add(int x, int y, LL s1, LL s2) {
    addedge(x, y, s1, s2);
    addedge(y, x, 0, -s2);
}

int S, T, T1, S1;
LL ans1, ans2;

int check() {
    static int bo[405], pre[405], prd[405];
    static LL dis1[405], dis2[405];
    for (int i = 1; i <= T1; ++i) {
        dis1[i] = 0;
        dis2[i] = 1LL << 50;
        bo[i] = 0;
    }
    dis1[S1] = 1 << 30;
    dis2[S1] = 0;
    queue<int> que;
    que.push(S1);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        bo[x] = 0;
        for (int k = first[x]; ~k; k = edge[k].nex)
            if (edge[k].w1 && edge[k].w2 + dis2[x] < dis2[edge[k].y]) {
                int y = edge[k].y;
                dis2[y] = dis2[x] + edge[k].w2;
                dis1[y] = min(edge[k].w1, dis1[x]);
                pre[y] = x;
                prd[y] = k;
                if (!bo[y]) {
                    bo[y] = 1;
                    que.push(y);
                }
            }
    }
    if (dis1[T1] == 0) return 0;
    ans1 += dis1[T1];
    ans2 += dis1[T1] * dis2[T1];
    for (int x = T1; x != S1; x = pre[x]) {
        edge[prd[x]].w1 -= dis1[T1];
        edge[prd[x] ^ 1].w1 += dis1[T1];
    }
    return 1;
}

LL solve() {
    ans1 = ans2 = 0;
    while (check());
    if (ans1 != n) return -1;
    else return ans2;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &K), n || m || K) {
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &si[i], &ti[i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d", &ci[j][i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d", &di[j][i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", &ei[i][j]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", &fi[i][j]);
        memset(first, -1, sizeof(first));
        tot = 0;
        S = n * 2 + m + 1; T = S + 1;
        for (int i = 1; i <= m; ++i)
            add(S, i, 1, 0);
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (ci[i][j] < ti[j]) 
                    add(i, j + m, 1, K * (max(ci[i][j], si[j]) - si[j]) + di[i][j]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (ti[i] + ei[i][j] < ti[j] && i != j)
                    add(i + n + m, j + m, 1, K * (max(ti[i] + ei[i][j], si[j]) - si[j]) + fi[i][j]);
        for (int i = 1; i <= n; ++i)
            add(i + n + m, T, 1, 0);
        add(T, S, m, 0);
        S1 = T + 1, T1 = S1 + 1;
        for (int i = 1; i <= n; ++i) {
            add(S1, i + m + n, 1, 0);
            add(i + m, T1, 1, 0);
        }
        //printf("%d %d\n", S, T);
        printf("%lld\n", solve());
    }
    return 0;
}