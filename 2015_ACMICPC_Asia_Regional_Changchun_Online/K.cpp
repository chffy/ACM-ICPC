#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
#include <vector>
using namespace std;

typedef __int128 LL;

LL getint() {
    char str[30];
    LL x = 0;
    scanf("%s", str);
    int n = strlen(str);
    for (int i = 0; i < n; ++i)
        x = x * 10 + str[i] - '0';
    return x;
}

const int N = 1e6 + 5;
int prime[N], m, bo[N];

long long solve(LL &k) {
    long long ans = 1;
    for (int i = 0; i < m; ++i)
        if (k % prime[i] == 0) {
            int L = 0;
            while (k % prime[i] == 0) {
                k /= prime[i];
                ++L;
            }
            ans = ans * L;
        }
    return ans; 
}

LL issqr2(LL x) {
    LL head = 0, tail = 1e12 + 1;
    while (head < tail - 1) {
        LL mid = (head + tail) / 2;
        if (mid * mid <= x) head = mid;
        else tail = mid;
    }
    if (head * head == x) return head;
    return 0;
}

LL issqr3(LL x) {
    LL head = 0, tail = 1e8 + 1;
    while (head < tail - 1) {
        LL mid = (head + tail) / 2;
        if (mid * mid * mid <= x) head = mid;
        else tail = mid;
    }
    if (head * head * head == x) return head;
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    m = 0;
    for (int i = 2; i < N; ++i)
        if (!bo[i]) {
            prime[m++] = i;
            for (int j = i * 2; j < N; j += i)
                bo[j] = 1;
        }
    while (T--) {
        LL k1, k2;
        k1 = getint();
        k2 = getint();
        long long ans1 = solve(k1), ans2 = solve(k2);
        LL k = __gcd(k1, k2);
        if (k != 1) {
            LL Z = k;
            if (issqr2(Z)) Z = issqr2(Z);
            else if (issqr3(Z)) Z = issqr3(Z);
            int L = 0;
            while (k1 % Z == 0) {
                k1 /= Z;
                L++;
            }
            ans1 = ans1 * L;
            L = 0;
            while (k2 % Z == 0) {
                ++L;
                k2 /= Z;
            }
            ans2 = ans2 * L;
        }
        if (k1 != 1 && issqr2(k1)) ans1 = ans1 + ans1;
        if (k2 != 1 && issqr2(k2)) ans2 = ans2 + ans2;
        printf("%I64d %I64d\n", ans1, ans2);
    }
    return 0;
}
