#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

int sum[2005];

class FoxMakingDice {
public:
    LL theCount(int N, int K) {
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                sum[i + j]++;
        LL ans = 0;
        for (int i = K; i <= 2 * N; ++i) {
            ans += (LL)sum[i] * (sum[i] - 1) * (sum[i] - 2) / 3;
        }
        return ans;
    }
};
