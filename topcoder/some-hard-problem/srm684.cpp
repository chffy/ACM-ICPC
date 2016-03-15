#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
using namespace std;

const int P = 1e9 + 7;
typedef long long LL;

int dp[55][1005][2];
int I[1005], inv[1005];
int C[1005][1005];
int sum[1005];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

class Permutant {
public:
    int counthis(vector <int> a) {
        int n = a.size();
        int m = 0;
        for (int i = 0; i < n; ++i) m += a[i];
        inv[0] = inv[1] = I[0] = I[1] = 1;
        for (int i = 2; i <= m; ++i) {
            inv[i] = (LL)(P - P / i) * inv[P % i] % P;
        }
        for (int i = 1; i <= m; ++i) {
            I[i] = (LL)I[i - 1] * i % P;
        }
        for (int i = 0; i <= m; ++i)
            for (int j = 0; j <= i; ++j)
                if (j == 0) C[i][j] = 1;
                else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        for (int i = 1; i <= m; ++i)
            for (int j = i; j <= m; ++j)
                updata(sum[i], C[j - 1][i - 1]);
        int ans = 0;
        for (int last = 0; last < n; ++last) {
            memset(dp, 0, sizeof(dp));
            swap(a[last], a[0]);
            dp[1][a[0]][0] = a[0];
            for (int i = 1; i < n; ++i)
                for (int j = 0; j <= m; ++j)
                    for (int k = 0; k < 2; ++k)
                        if (dp[i][j][k]) {
                            int res = (LL)dp[i][j][k] * inv[a[i]] % P;
                            updata(dp[i + 1][j][k], res);
                            updata(dp[i + 1][j + a[i]][k ^ 1], res);
                        }
            for (int j = 1; j <= m; ++j)
                for (int k = 0; k < 2; ++k)
                    dp[n][j][k] = (LL)dp[n][j][k] * I[j - 1] % P * I[m - j] % P;
            for (int j = 0; j <= m; ++j)
                for (int k = 0; k < 2; ++k) {
                    int fac = sum[j];
                    if (k == 1) fac = (P - fac) % P;
                    updata(ans, (LL)dp[n][j][k] * fac % P);
                }
            swap(a[last], a[0]);
        }
        return ans;
    }
};
