#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

typedef long long LL;

class MagicalSource {
public:
    LL calculate(LL x) {
        LL ans = x, p = 0;
        for (int i = 1; i <= 12; ++i) {
            p = p * 10 + 1;
            if (x % p == 0)
                ans = min(ans, x / p);
        }
        return ans;
    }
};
