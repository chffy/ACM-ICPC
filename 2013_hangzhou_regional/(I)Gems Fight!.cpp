#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

int num[1 << 21], sum[1 << 21];
int item[50][50];
int f[1 << 21][2];

int main() {
    int G, B, S;
    while (scanf("%d%d%d", &G, &B, &S), G || B || S) {
        for (int i = 0; i < 1 << B; ++i)
            num[i] = 0;
        memset(item, 0, sizeof(item));
        for (int i = 0; i < B; ++i) {
            int n;
            scanf("%d", &n);
            while (n--) {
                int x;
                scanf("%d", &x);
                item[i][x]++;
            }
        }
        for (int T = 1; T <= G; ++T) {
            for (int mask = 0; mask < 1 << B; ++mask)
                sum[mask] = 0;
            for (int i = 0; i < B; ++i) {
                sum[1 << i] = item[i][T];
                num[1 << i] += sum[1 << i] / S;
            }
            for (int mask = 0; mask < 1 << B; ++mask)
                if (__builtin_popcount(mask) > 1) {
                    int lowbit = mask & -mask;
                    sum[mask] = sum[mask ^ lowbit] + sum[lowbit];
                    num[mask] += sum[mask] / S;
                }
        }
        f[0][0] = f[0][1] = 0;
        for (int mask = 1; mask < 1 << B; ++mask) {
            f[mask][0] = 1 << 29;
            f[mask][1] = -(1 << 29);
            for (int i = 0; i < B; ++i)
                if (mask >> i & 1) {
                    int S = (1 << B) - 1;
                    int opt = mask ^ (1 << i);
                    int v = num[opt ^ S] - num[mask ^ S];
                    //printf("%d\n", v);
                    if (v > 0) {
                        f[mask][1] = max(f[mask][1], f[opt][1] + v);
                        f[mask][0] = min(f[mask][0], f[opt][0] - v);
                    }
                    else {
                        f[mask][1] = max(f[mask][1], f[opt][0]);
                        f[mask][0] = min(f[mask][0], f[opt][1]);
                    }
                }
        }
        printf("%d\n", f[(1 << B) - 1][1]);
    }
    return 0;
}