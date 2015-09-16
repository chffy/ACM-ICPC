#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    int val, cost, num;
}item[205];

int f[2][50105], g[50105];

void fill(int f[], int m, int flag) {
    for (int i = 0; i <= m; ++i) {
        if (flag == 1) f[i] = (1 << 29);
        else f[i] = 0;
    }
}

int calc(int f[], int a, int cost) {
    return f[a] - g[a] * cost; 
}

int check(int f[], int a, int b, int cost, int flag) {
    if (calc(f, a, cost) > calc(f, b, cost) && flag == 1) return 1;
    if (calc(f, a, cost) < calc(f, b, cost) && flag == -1) return 1;
    return 0;
}

int solve(int n, int m, int K, int flag) {
    int cur = 0, nex = 1;
    fill(f[cur], m, flag);
    f[cur][0] = 0;
    for (int i = 1; i <= n; ++i) {
        fill(f[nex], m, flag);
        int p = item[i].val;
        for (int j = 0; j < p; ++j) {
            int head = 1, tail = 0;
            int mark = 0;
            static int a[100005];
            for (int k = j; k <= m; k += p) {
                g[k] = k / p;
                while (head <= tail && check(f[cur], a[tail], k, item[i].cost, flag))
                    --tail;
                if (head <= tail && (k - a[head]) > item[i].num * p) ++head;
                a[++tail] = k;
                f[nex][k] = calc(f[cur], a[head], item[i].cost) + g[k] * item[i].cost;
            }
        }
        swap(cur, nex);
    }
    if (flag == 1) {
        int p = 1 << 30;
        for (int i = K; i <= m; ++i) {
            p = min(p, f[cur][i]);
        }
        return p;
    }
    for (int i = 0; i <= m; ++i) {
        //cout << f[cur][i] << endl;
        if (f[cur][i] >= K) return i;

    }
    return -1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &item[i].val, &item[i].cost, &item[i].num);
            sum += item[i].val * item[i].num;
        }
        sum = min(sum, p + 100);
        int minsize = solve(n, sum, p, 1);
        int mincost = -1;
        sum = 0;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &item[i].cost, &item[i].val, &item[i].num);
            sum += item[i].val * item[i].num;
        }
        sum = min(sum, 50000);
        if (minsize != -1) mincost = solve(m, sum, minsize, -1);
        if (mincost == -1) puts("TAT");
        else printf("%d\n", mincost);
    }
    return 0;
}
