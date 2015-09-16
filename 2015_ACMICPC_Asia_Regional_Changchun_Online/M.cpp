#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
const int D = 20;
int tot;
int first[N];

struct Edge {
    int y, nex;
}edge[N << 1];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int parent[D][N], dep[N];
long double val1[D][N], val2[D][N];
long double f[N], sum[N];
int degree[N];

void dfs(int x, int fa) {
    f[x] = 0;
    long double a = (long double)(degree[x] - 1) / degree[x];
    a = a / ((a - 1) * (a - 1));
    dep[x] = dep[fa] + 1;
    parent[0][x] = fa;
    sum[x] = 0;
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        dfs(y, x);
        sum[x] += f[y];
    }
    f[x] = 2 * a;
    if (degree[x] > 1)
        f[x] += a * sum[x] / (degree[x] - 1);
    f[x] = f[x] / degree[x];
}

long double g[N], t[N];

void dfs1(int x, int fa) {
    for (int k = first[x]; k != -1; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        long double a = (long double)(degree[x] - 1) / degree[x];
        a = a / ((a - 1) * (a - 1));
        long double s1 = sum[x] - f[y] + g[fa];
        g[x] = 2 * a;
        if (degree[x] > 1)
            g[x] += a * s1 / (degree[x] - 1);
        g[x] = g[x] / degree[x];
        t[y] = g[x];
        dfs1(y, x);
    }
}

long double gett(int x, int y) {
    int flag = 0;
    if (dep[x] < dep[y]) {
        flag = 1;
        swap(x, y);
    }
    long double ans = 0;
    for (int i = D - 1; i >= 0; --i)
        if (dep[parent[i][x]] >= dep[y]) {
            if (flag == 0) ans += val1[i][x];
            else ans += val2[i][x];
            x = parent[i][x];
            ans += (long double)(1 << i);
        }
    if (x == y) return ans;
    for (int i = D - 1; i >= 0; --i)
        if (parent[i][x] != parent[i][y]) {
            if (flag == 0) ans += val1[i][x] + val2[i][y];
            else ans += val2[i][x] + val1[i][y];
            x = parent[i][x];
            y = parent[i][y];
            ans += (long double)(1 << (i + 1));
        }
    ans = ans + 2;
    if (flag == 0) ans += val1[0][x] + val2[0][y];
    else ans += val2[0][x] + val1[0][y];
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        memset(first, -1, sizeof(first));
        memset(degree, 0, sizeof(degree));
        tot = 0;
        for (int i = 1; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            ++x;
            ++y;
            addedge(x, y);
            addedge(y, x);
            ++degree[x];
            ++degree[y];
        }
        dfs(1, 0);
        dfs1(1, 0);
        for (int i = 1; i <= n; ++i) {
            val1[0][i] = f[i];
            val2[0][i] = t[i];
        }
        for (int k = 1; k < D; ++k)
            for (int i = 1; i <= n; ++i) {
                int p = parent[k - 1][i];
                parent[k][i] = parent[k - 1][p];
                val1[k][i] = val1[k - 1][i] + val1[k - 1][p];
                val2[k][i] = val2[k - 1][i] + val2[k - 1][p];
            }
        int q;
        scanf("%d", &q);
        static int ca = 0;
        if (ca > 0) puts("");
        else ca = 1;
        while (q--) {
            int ki;
            scanf("%d", &ki);
            long double ans = 0;
            int x;
            scanf("%d", &x);
            ++x;
            for(int i = 1; i <= ki; ++i) {
                int y;
                scanf("%d", &y);
                ++y;
                ans += gett(x, y);
                x = y;
            }
            long long p = (long long)(ans + 1e-9);
            printf("%lld.0000\n", p);
        }
    }
    return 0;
}
