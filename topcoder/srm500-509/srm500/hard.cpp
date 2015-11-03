#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int N = 1e5 + 5;
typedef long long LL;

const int P = 500500573;
int frac[N], rfrac[N], inv[N];
int sum[10], level[N];

class ProductAndSum {
public:
    int getSum(int p2, int p3, int p5, int p7, int S) {
        frac[0] = frac[1] = inv[0] = inv[1] = 1;
        rfrac[0] = rfrac[1] = 1;
        for (int i = 2; i < N; ++i) {
            frac[i] = (LL)i * frac[i - 1] % P;
            inv[i] = ((LL)P - P / i) * inv[P % i] % P;
            rfrac[i] = (LL)rfrac[i - 1] * inv[i] % P;
        }
        level[0] = 0;
        for (int i = 1; i < N; ++i) {
            level[i] = ((LL)level[i - 1] * 10 + 1) % P;
        }
        sum[5] = p5;
        sum[7] = p7;
        int ans = 0;
        for (sum[4] = 0; sum[4] <= p2 / 2; ++sum[4])
            for (sum[8] = 0; sum[8] <= (p2 - sum[4] * 2) / 3; ++sum[8])
                for (sum[9] = 0; sum[9] <= p3 / 2; ++sum[9])
                    for (sum[6] = 0; sum[6] <= min(p2 - sum[4] * 2 - sum[8] * 3, p3 - sum[9] * 2); ++sum[6]) {
                        sum[2] = p2 - sum[6] - sum[4] * 2 - sum[8] * 3;
                        sum[3] = p3 - sum[6] - sum[9] * 2;
                        int tot = 0;
                        sum[1] = S;
                        for (int i = 2; i < 10; ++i) {
                            tot += sum[i];
                            sum[1] -= sum[i] * i;
                        }
                        tot += sum[1];
                        if (sum[1] < 0) continue;
                        int res = frac[tot - 1];
                        for (int i = 1; i < 10; ++i)
                            res = (LL)res * rfrac[sum[i]] % P;
                        for (int i = 1; i < 10; ++i)
                            ans = (ans + (LL)i * level[tot] % P * res % P * sum[i] % P) % P;
                    }
        return ans;
    }
};
