#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int N = 1e5 + 5;

typedef long long LL;

int first[N], m1[N], m2[N], m3[N];
int tot, cnt;
int bo[N], degree[N];
int d[N][2];

struct Edge {
    int y, s, nex;
}edge[N << 1];

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}

LL sum[4][4];

int main() {
    int n, m;
    cnt = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            first[i] = -1;
            degree[i] = 0;
            d[i][0] = d[i][1] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &m1[i], &m2[i], &m3[i]);
            m3[i] ^= 1;
            ++degree[m1[i]];
            ++degree[m2[i]];
            d[m1[i]][m3[i]]++;
            d[m2[i]][m3[i]]++;
        }
        for (int i = 1; i <= m; ++i)
            if (make_pair(degree[m1[i]], m1[i]) < make_pair(degree[m2[i]], m2[i])) {
                addedge(m1[i], m2[i], m3[i]);
            }
            else addedge(m2[i], m1[i], m3[i]);
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= m; ++i) {
            ++cnt;
            int x = m1[i], y = m2[i];
            for (int k = first[x]; k != -1; k = edge[k].nex)
                if (edge[k].y != y) {
                    bo[edge[k].y] = (cnt << 1) | edge[k].s;
                }
            for (int k = first[y]; k != -1; k = edge[k].nex)
                if (edge[k].y != x) {
                    if ((bo[edge[k].y] >> 1) == cnt)
                        sum[3][(bo[edge[k].y] & 1) + edge[k].s + m3[i]]++; 
                }
        }
        for (int i = 1; i <= n; ++i) {
            sum[2][0] += (LL)d[i][0] * (d[i][0] - 1) / 2;
            sum[2][1] += (LL)d[i][0] * d[i][1];
            sum[2][2] += (LL)d[i][1] * (d[i][1] - 1) / 2;
        }
        for (int i = 0; i <= 3; ++i) {
            sum[2][i] -= sum[3][i] * (3 - i);
            if (i > 0)
                sum[2][i - 1] -= sum[3][i] * i;
        }
        for (int i = 1; i <= m; ++i) {
            sum[1][m3[i]] += n - 2; 
        }
        for (int i = 0; i <= 3; ++i) {
            sum[1][0] -= sum[2][i] * (2 - i) + sum[3][i] * (3 - i);
            sum[1][1] -= sum[2][i] * i + sum[3][i] * i;
        }
        sum[0][0] = (LL)n * (n - 1) * (n - 2) / 6;
        for (int i = 1; i <= 3; ++i)
            for (int j = 0; j <= 3; ++j)
                sum[0][0] -= sum[i][j];
        LL ans = sum[3][0] + sum[3][1] + sum[2][0] * 2 + sum[2][1]
            + sum[1][0] * 3 + sum[1][1] + sum[0][0] * 4;
        cout << ans % 999983 << endl;
    }
    return 0;
}
