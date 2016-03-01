#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

int sum[2005];

class Starport {
public:
    double getExpectedTime(int N, int M) {
        int K = __gcd(N, M);
        LL ans = (LL)(N / K) * (N / K - 1) / 2 * K;
        return (double)ans / (N / K);
    }
};
