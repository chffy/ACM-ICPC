#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 5e5 + 5;
int a[N], c[N];
pair<int, int> b[N];

int solve(int l, int r) {
    return ((LL)r * (r + 1) / 2 - (LL)l * (l - 1) / 2) % P; 
}

int main() {
    int n;
    int m = 3, t = 3;
    b[1] = make_pair(1, 1);
    b[2] = make_pair(2, 3);
    a[1] = 1; a[2] = 2;
    a[3] = 2;
    int r;
    for (int i = 3; i < N; ++i) {
        for (int j = 1; j <= a[i] && m + 1 < N; ++j)
            a[++m] = i;
        b[i] = make_pair(t + 1, t + a[i]);
        t += a[i];
        if (t >= (int)1e9) {
            r = i;
            break;
        }
    }
    for (int i = 1; i < N; ++i) {
        c[i] = ((LL)c[i - 1] + (LL)i % P * solve(b[i].first, b[i].second)) % P;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int t = lower_bound(b + 1, b + 1 + r, make_pair(n + 1, -1)) - b - 1;
        int ans = c[t - 1];
        ans = (ans + (LL)t % P * solve(b[t].first, n)) % P;
        printf("%d\n", ans);
    }
    return 0;
}
