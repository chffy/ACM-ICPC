#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 5e5 + 5;

vector<int> ver[N];
int mu[N], prime[N], m, bo[N];
int mark[N], a[N];

void modify(int x, int k, long long &ans) {
    ans -= (long long)mu[x] * mark[x] * (mark[x] - 1) / 2;
    mark[x] += k;
    ans += (long long)mu[x] * mark[x] * (mark[x] - 1) / 2;
}

int main() {
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i)
            ver[j].push_back(i);
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!bo[i]) {
            prime[m++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < m && prime[j] * i < N; ++j) {
            bo[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    long long ans = 0;
    memset(bo, 0, sizeof(bo));
    for (int i = 1; i <= q; ++i) {
        int x;
        scanf("%d", &x);
        int k = 0;
        if (bo[x]) {
            bo[x] = 0;
            k = -1;
        }
        else {
            bo[x] = 1;
            k = 1;
        }
        for (int j = 0; j < ver[a[x]].size(); ++j) {
            modify(ver[a[x]][j], k, ans);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
