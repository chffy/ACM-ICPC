#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 37;

struct Edge {
    int y, nex;
}edge[N * 2];

int first[N], tot, n;

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

LL f[N][N][N][2];
int size[N];

void dfs(int x, int fa) {
    size[x] = 1;
    for (int k = first[x]; ~k; k = edge[k].nex)
        if (edge[k].y != fa) {
            int y = edge[k].y;
            dfs(y, x);
            size[x] += size[y];
        }
    f[x][0][0][0] = 1;
    f[x][1][0][1] = 1;
    for (int k = first[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        for (int i = size[x]; i >= 0; --i)
            for (int j = size[x]; j >= 0; --j)
                for (int _i = min(size[y], i); _i >= 0; --_i)
                    for (int _j = min(size[y], j); _j >= 0; --_j) {
                        if (_i == 0 && _j == 0) continue;
                        f[x][i][j][1] += f[x][i - _i][j - _j][1] * (f[y][_i][_j][0] + f[y][_i][_j][1]);
                        f[x][i][j][0] += f[x][i - _i][j - _j][0] * f[y][_i][_j][0];
                        if (_j != 0)
                            f[x][i][j][0] += f[x][i - _i][j - _j][0] * f[y][_i][_j - 1][1];
                    }
    }
}

LL g[N][N];

class CentaurCompany {
public:
    double getvalue(vector <int> a, vector <int> b) {
        memset(first, -1, sizeof(first));
        n = a.size() + 1;
        for (int i = 0; i < n - 1; ++i) {
            int x = a[i], y = b[i];
            addedge(x, y);
            addedge(y, x);
        }
        dfs(1, 0);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                for (int mask = 0; mask < 2; ++mask)
                    if (f[1][i][j][mask]) {
                        if (mask == 0) g[i][j] += f[1][i][j][mask];
                        else g[i][j + 1] += f[1][i][j][mask];
                    }
        LL ans = 0;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                if (g[i][j]) {
                    int num_slot = i;
                    int connect = j - 1;
                    connect -= i / 2;
                    num_slot &= 1;
                    if (connect <= 0) continue;
                    int add_slot = connect * 2 - num_slot;
                    ans += add_slot * g[i][j];
                }
        ans *= 2;
        LL ans1 = 1LL << n;
        return (double)ans / ans1;
    }
};
