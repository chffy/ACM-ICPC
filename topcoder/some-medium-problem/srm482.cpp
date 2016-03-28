#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
#include <deque>
using namespace std;

int power[20];
int num[20], mark[20];

void solve(int n, int a, int b, int c, int &k) {
    if (n == 0 || k == 0) return ;
    solve(n - 1, a, c, b, k);
    if (k == 0) return ;
    --k;
    num[n] = b;
    solve(n - 1, c, b, a, k);
}

int check(int n, int a, int b, int c) {
    if (n == 0) return 0;
    if (mark[n] == num[n]) return check(n - 1, a, b, c);
    else if (num[n] == c) {
        int ans = power[n - 1] - 1;
        for (int i = 1; i < n; ++i) mark[i] = b;
        mark[n] = c;
        return ans + check(n - 1, b, a, c) + 1;
    }
    int ans = (power[n - 1] - 1) * 2;
    for (int i = 1; i < n; ++i) mark[i] = a;
    mark[n] = b;
    return ans + check(n - 1, a, b, c) + 2;
}

class HanoiGoodAndBad {
public:
    int moves(int N, int Dave) {
        power[0] = 1;
        for (int i = 1; i < 20; ++i)
            power[i] = power[i - 1] * 3;
        solve(N, 0, 2, 1, Dave);
        return check(N, 0, 2, 1);
    }
};
