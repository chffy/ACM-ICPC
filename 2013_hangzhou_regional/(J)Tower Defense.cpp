#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int P = 1e9 + 7;
typedef long long LL;

int f[205][205][205];
int g[205][205][205];
int C[205][205], fac[205];

int main() {
    int T;
    scanf("%d", &T);
    fac[0] = 1;
    for (int i = 0; i < 205; ++i)
        for (int j = 0; j <= i; ++j)
            C[i][j] = (j == 0) ? 1 : (C[i - 1][j] + C[i - 1][j - 1]) % P;
    for (int i = 1; i < 205; ++i)
        fac[i] = (LL)fac[i - 1] * i % P;
    f[0][0][0] = 1;
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= 200; ++j)
            for (int k = 1; k <= 200; ++k) {
                int &res = f[i][j][k];
                res = ((LL)j * f[i - 1][j - 1][k - 1]) % P;
                if (j > 1 && k > 1) {
                    res = ((LL)C[j][2] * f[i - 1][j - 2][k - 2] + res) % P;
                }
                if (i > 1 && k > 1) {
                    res = ((LL)(i - 1) * j * f[i - 2][j - 1][k - 2] + res) % P;
                }
            }
    for (int i = 0; i <= 200; ++i)
        for (int j = 0; j <= 200; ++j)
            for (int k = 0; k <= 200; ++k) {
                int &res = g[i][j][k];
                if (k) res = g[i][j][k - 1];
                else res = 0;
                if (i >= k && j >= k) {
                    res = (res + (LL)C[i][k] * C[j][k] % P * fac[k]) % P; 
                }
            }
    for (int i = 0; i <= 200; ++i)
        for (int j = 0; j <= 200; ++j)
            for (int k = 1; k <= 200; ++k)
                f[i][j][k] = (f[i][j][k] + f[i][j][k - 1]) % P;
    while (T--) {
        int n, m, p, q;
        scanf("%d%d%d%d", &n, &m, &p, &q);
        int ans = 0;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j) {
                ans = (ans + (LL)f[i][j][p] * g[n - i][m - j][q] % P * C[n][i] % P * C[m][j] % P) % P;
                //printf("%d %d %d\n", i, j, f[i][j][p]);
            }
        printf("%d\n", (ans + P - 1) % P);
    }
    return 0;
}