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

int check(int sx, int sy, int gx, int gy) {
    int ans = abs(sy - gy);
    int t = abs(sx - gx);
    int tmp = min(ans, t);
    t = t - tmp + (ans - tmp) % 2;
    if (t % 2 != 0) return 1 << 30;
    //if (ans + t <= 10) printf("%d\n", ans + t);
    return ans + t;
}

class SilverDistance {
public:
    int minSteps(int sx, int sy, int gx, int gy) {
        int ans = 1 << 30;
        for (int i = 0; i <= 5000000; ++i) {
            ans = min(ans, check(sx, sy + i, gx, gy) + i);
        }
        return ans;
    }
};

