#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int P = 1e9 + 7;
typedef long long LL;
const int N = 3005;

int first[N], tot;

struct Edge {
    int y, nex;
}edge[N << 1];

void addedge(int x, int y) {
    edge[tot] = (Edge) {y, first[x]};
    first[x] = tot++;
}

int bo[N], pre[N], seq[N], n;

int get_seq(int s, int t) {
    bo[s] = 1;
    pre[s] = -1;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int k = first[x]; ~k; k = edge[k].nex)
            if (!bo[edge[k].y]) {
                bo[edge[k].y] = 1;
                pre[edge[k].y] = x;
                que.push(edge[k].y);
            }
    }
    int m = 0;
    for (int x = t; x != -1; x = pre[x]) {
        seq[++m] = x;
    }
    reverse(seq + 1, seq + 1 + m);
    return m;
}

int inv[N], I[N];

void init() {
    inv[0] = inv[1] = I[0] = I[1] = 1;
    for (int i = 2; i < N; ++i) {
        I[i] = i;
        inv[i] = ((LL)P - P / i) * inv[P % i] % P; 
    }
    for (int i = 2; i < N; ++i) {
        I[i] = (LL)I[i - 1] * I[i] % P;
        inv[i] = (LL)inv[i - 1] * inv[i] % P;
    }
}

int C(int n, int m) {
    return (LL)I[n] * inv[m] % P * inv[n - m] % P;
}

int size[N];

int dfs(int x, int fa, int mark) {
    size[x] = 0;
    if (bo[x] != 0 && bo[x] != mark) return 1;
    size[x] = 1;
    int res = 1;
    for (int k = first[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        res = (LL)res * dfs(y, x, mark) % P;
        size[x] += size[y];
    }
    int m = 0;
    for (int k = first[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (y == fa) continue;
        res = (LL)res * C(size[x] - m - 1, size[y]) % P;
        m += size[y];
    }
    return res;
}

int num[N];

class TwoEntrances {
public:
    int count(vector <int> a, vector <int> b, int s1, int s2) {
        init();
        int ans = 0;
        memset(first, -1, sizeof(first));
        n = a.size() + 1;
        for (int i = 0; i < a.size(); ++i) {
            addedge(a[i], b[i]);
            addedge(b[i], a[i]);
        }
        int m = get_seq(s1, s2);
        memset(bo, 0, sizeof(bo));
        for (int i = 1; i <= m; ++i) bo[seq[i]] = 2;
        for (int i = 1; i <= m; ++i) {
        	bo[seq[i]] = 1;
            int res = dfs(s1, -1, 1);
            res = (LL)res * C(n, size[s1]) % P;
            res = (LL)res * dfs(s2, -1, 2) % P;
            num[i] = res;
           // printf("%d %d\n", i, res);
        }
        for (int i = m - 1; i > 0; --i) {
        	num[i] = (num[i] + P - num[i + 1]) % P;
        }
        for (int i = 1; i <= m; ++i) ans = (ans + num[i]) % P;
        return ans;
    }
};
