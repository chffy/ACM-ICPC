#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long LL;
const double Limit = 1LL << 40;

LL f[63];
int a[63];

LL dfs(int x, int k) {
    if (x == 0) return 0;
    LL res = 0;
    if (f[x - 1] <= k) {
        k -= f[x - 1];
        res = 1;
    }
    return (res << (x - 1)) | dfs(x - 1, k); 
}

class BitwiseEquations {
public:
    LL kthPlusOrSolution(int x, int k) {
        f[0] = 1;
        for (int i = 0; i + 1 < 63; ++i) {
            int fac = 1;
            if (x % 2 == 0) ++fac, a[i + 1] = 1;
            f[i + 1] = f[i] * fac;
            if (f[i + 1] >= Limit) f[i + 1] = Limit;
            x /= 2;
        }
        return dfs(63, k);
    }
};
