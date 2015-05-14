#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

typedef long long LL;

const int N = 1e6 - 5;

LL solve(int a, int b, int c) {
    LL ans = abs((LL)a * b - c);
    int L = a - N, R = a + N;
    if (L <= 0) L = 1;
    for (int i = L; i <= R; ++i) {
        LL tmp = c / i;
        if (tmp > 0) ans = min(ans, abs(a - i) + abs(tmp - b) + abs(tmp * i - c));
        ans = min(ans, abs(a - i) + abs(tmp + 1 - b) + abs((tmp + 1) * i - c));
    }
    for (int i = 1; i <= N; ++i) {
        LL tmp = c / i;
        if (tmp > 0) ans = min(ans, abs(a - i) + abs(tmp - b) + abs(tmp * i - c));
        ans = min(ans, abs(a - i) + abs(tmp + 1 - b) + abs((tmp + 1) * i - c));
    }
    return ans;
}

class CorrectMultiplication {
public:
    LL getMinimum(int a, int b, int c) {
        
        return min(solve(a, b, c), solve(b, a, c));
    }
};
