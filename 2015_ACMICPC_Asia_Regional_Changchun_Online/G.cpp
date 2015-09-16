#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int a[100000];

int main() {
    int n, m;
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) {
            int l, r;
            scanf("%d%d", &l, &r);
            int ans = a[l];
            for (int j = l; j <= r; ++j)
                ans = max(ans, a[j]);
            printf("%d\n", ans);
        }
    }
    return 0;
}
