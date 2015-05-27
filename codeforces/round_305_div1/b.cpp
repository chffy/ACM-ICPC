#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 5e5 + 5;

int height[N];
int ans[N], ll[N], rr[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &height[i]);
    static int stack[N];
    int p = 0;
    for (int i = 1; i <= n; ++i) {
        while (p && height[i] <= height[stack[p]])
            --p;
        if (p == 0) ll[i] = 1;
        else ll[i] = stack[p] + 1;
        stack[++p] = i;
    }
    p = 0;
    for (int i = n; i >= 1; --i) {
        while (p && height[i] <= height[stack[p]])
            --p;
        if (p == 0) rr[i] = n;
        else rr[i] = stack[p] - 1;
        stack[++p] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int len = rr[i] - ll[i] + 1;
        ans[len] = max(ans[len], height[i]);
    }
    for (int i = n - 1; i >= 1; -- i)
        ans[i] = max(ans[i], ans[i + 1]);
    for (int i = 1; i <= n; ++i)
        printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}
