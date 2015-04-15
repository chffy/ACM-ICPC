#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int P = 1e9 + 7;
typedef long long LL;

int C[2005][2005], f[2005];

int calc(int x, int y, int K) {
    if (y == 0) return 0;
    int k = __gcd(x, y) + 1;
    if (k < K) return 0;
    return C[k][K];
}

class Spacetsk {
public:
    int countsets(int L, int H, int K) {
        for (int i = 0; i <= 2004; ++i) {
            C[i][0] = 1;
            for (int j = 1; j <= i; ++j)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
        }
       // printf("%d %d %d\n", L, H, K);
        if (K == 1) {
            return (L + 1) * (H + 1);
        }
        for (int i = 0; i <= L; ++i) {
            if (i != 0) f[i] = f[i - 1];
            for (int j = 0; j <= H; ++j) {
                if (j == 0) continue;
                int k = __gcd(i, j);
                int _i = i / k, _j = j / k;
                f[i] = ((LL)f[i] + calc(i, j, K) + P - calc(i - _i, j - _j, K)) % P;
            }
        }
        int ans = 0;
        for (int i = 0; i <= L; ++i) {
            ans = (ans + f[i]) % P;
            ans = (ans + f[L - i]) % P;
            ans = (ans + P - calc(0, H, K)) % P;
        }
        return ans;
    }
};

