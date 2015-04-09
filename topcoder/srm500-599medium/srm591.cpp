#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

class PyramidSequences {
public:
    
    LL distinctPairs(int N, int M) {
        --N, --M;
        int g = __gcd(N, M);
        N /= g, M /= g;
        LL ans1 = (LL)N * M * (g - 1);
        LL ans2 = (LL)(N / 2 + 1) * (M / 2 + 1);
        ans2 += (LL)((N - 1) / 2 + 1) * ((M - 1) / 2 + 1);
        return ans1 + ans2; 
    }
};
