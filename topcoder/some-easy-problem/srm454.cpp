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

int calc(int a, int b) {
    int d[10];
    memset(d, 0, sizeof(d));
    for (int i = 0; i < 10; ++i) {
        d[i] = (a % 10) ^ (b % 10);
        a /= 10;
        b /= 10;
    }
    int c = 0;
    for (int i = 9; i >= 0; --i)
        c = c * 10 + d[i] % 10;
    return c;
}

class DoubleXor {
public:
    int calculate(int N) {
        int ans = N;
        for (int i = N - 1; i > 0; --i)
            ans = calc(ans, i);
        return ans;
    }
};
