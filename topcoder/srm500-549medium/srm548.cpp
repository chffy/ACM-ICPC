#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std; 

typedef long long LL;

int pd(int height, int width, LL S, LL p, LL q) {
    if (p > height || q > width) return 0;
    LL ret = p * q;
    LL re = 2 * S - ret * (q - 1);
    if (re < 0) return 0;
    if (ret * (p - 1) > re) return 0;
    re -= ret * (p - 1) * width;
    if (re < 0) return 0;
    if (re % (ret * 2) != 0) return 0;
    re /= ret * 2;
    LL x = re / width;
    LL y = re - x * width;
    if (x + p > height || y + q > width) return 0;
    return 1;
}

int check(int height, int width, LL S, LL area) {
    if (area > 1000000000) return 0;
    if (area * (area - 1) / 2 > S) return 0;
    for (int i = 1; (LL)i * i <= area; ++i)
        if (area % i == 0) {
            LL p = i, q = area / i;
            if (pd(height, width, S, p, q) ||
                pd(height, width, S, q, p))
                return 1;
    }
    return 0;
}

class RectangularSum {
public:
    LL minimalArea(int height, int width, LL S) {
        LL ans = (LL)height * width + 1;
        for (int i = 1; (LL)i * i <= 2 * S; ++i)
            if (2 * S % i == 0) {
                if (check(height, width, S, i))
                    ans = min(ans, (LL)i);
                if (check(height, width, S, 2 * S / i))
                    ans = min(ans, (LL)2 * S / i);
            }
        if (ans > (LL)height * width) return -1;
        else return ans;
    }
};
