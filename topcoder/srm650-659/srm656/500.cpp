#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int a[2500];
const int N = 1e6 + 5;
int f[2505][2], sum[2505];
const int P = 1e9 + 7;
int I[N], inv[N];
typedef long long LL;
void init() {
    I[0] = I[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i) {
        I[i] = i;
        inv[i] = ((LL)P - P / i) * inv[P % i] % P;
    }
    for (int i = 2; i < N; ++i) {
        I[i] = (LL)I[i - 1] * I[i] % P;
        inv[i] = (LL)inv[i - 1] * inv[i] % P;
    }
}
 
int C(int n, int m) {
    return (LL)I[n] * inv[m] % P * inv[n - m] % P;
}
 
class PermutationCounts {
public:
    int countPermutations(int N, vector <int> pos) {
        init();
        sort(pos.begin(), pos.end());
        int n = 0, p = 0;
        for (int i = 0; i < pos.size(); ++i) {
            a[++n] = (i == 0) ? pos[i] : (pos[i] - pos[i - 1]);
            p = pos[i];
        }
        a[++n] = N - p;
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + a[i];
        f[0][0] = 1;
        for (int i = 0; i < n; ++i)
            for (int p = 0; p < 2; ++p)
                if (f[i][p]) {
                    int num = N - sum[i];
                    for (int j = i + 1; j <= n; ++j) {
                        int L = sum[j] - sum[i];
                        int opt = p ^ ((j - i - 1) & 1);
                        f[j][opt] = (f[j][opt] + (LL)f[i][p] * C(num, L)) % P;
                    }
                }
        return (f[n][0] + P - f[n][1]) % P;
    }
};
