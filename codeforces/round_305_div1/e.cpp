#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int N = 5e5 + 5;
int start[N], len[N], rank[N], sa[N], height[20][N];
int str[N], mark[N];

void suffix(int n) {
    static int sum[N];
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; ++i)
        ++sum[str[i]];
    for (int i = 1; i < N; ++i)
        sum[i] += sum[i - 1];
    for (int i = 1; i <= n; ++i)
        sa[sum[str[i]]--] = i;
    for (int i = 1, p = 0; i <= n; ++i) {
        if (i == 1 || str[sa[i]] != str[sa[i - 1]])
            ++p;
        rank[sa[i]] = p;
    }
    for (int j = 1; rank[sa[n]] != n; j <<= 1) {
        memset(sum, 0, sizeof(int) * (n + 1));
        static int sb[N], rank1[N], rank2[N];
        for (int i = 1; i <= n; ++i) {
            sb[i] = sa[i];
            rank1[i] = rank[i];
            if (i + j > n) rank2[i] = 0;
            else rank2[i] = rank[i + j];
            sum[rank[i]]++;
        }
        for (int i = 1; i <= n; ++i)
            sum[i] += sum[i - 1];
        for (int i = n; i >= 1; --i)
            if (sb[i] > j) {
                int y = sb[i] - j;
                sa[sum[rank[y]]--] = y;
            }
        for (int i = n - j + 1; i <= n; ++i) {
            sa[sum[rank[i]]--] = i;
        }
        for (int i = 1, p = 0; i <= n; ++i) {
            if (i == 1 || rank1[sa[i]] != rank1[sa[i - 1]] ||
                rank2[sa[i]] != rank2[sa[i - 1]])
                ++p;
            rank[sa[i]] = p;
        }
    }
    for (int i = 1, p = 0; i <= n; ++i) {
        if (rank[i] == 1) continue;
        int j = sa[rank[i] - 1];
        while (i + p <= n && j + p <= n && str[i + p] == str[j + p])
            ++p;
        height[0][rank[i]] = p;
        if (p) --p;
    }
}

vector<int> tree[N * 4];

void build(int k, int m, int n) {
    if (m == n) {
        tree[k].push_back(mark[sa[m]]);
        return ;
    }
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    build(z1, m, mid);
    build(z2, mid + 1, n);
    tree[k] = tree[z1];
    tree[k].insert(tree[k].end(), tree[z2].begin(), tree[z2].end());
    sort(tree[k].begin(), tree[k].end());
}

int query(int k, int m, int n, int p, int q, int l, int r) {
    if (m > q || n < p) return 0;
    if (m >= p && n <= q) {
        return upper_bound(tree[k].begin(), tree[k].end(), r) -
            lower_bound(tree[k].begin(), tree[k].end(), l);
    }
    int z1 = k << 1, z2 = z1 + 1, mid = (m + n) >> 1;
    return query(z1, m, mid, p, q, l, r) +
        query(z2, mid + 1, n, p, q, l, r);
}

int LOG[N];

void init() {
    for (int i = 0; 1 << i < N; ++i)
        LOG[1 << i] = i;
    for (int i = 2; i < N; ++i)
        if (LOG[i] == 0) LOG[i] = LOG[i - 1];
}

int rmq(int l, int r) {
    if (l > r) return 1 << 30;
    int s = LOG[r - l + 1];
    return min(height[s][l], height[s][r - (1 << s) + 1]);
}

pair<int, int> find(int x, int n, int len) {
    pair<int, int> ans;
    int head = 1, tail = x;
    while (head < tail - 1) {
        int mid = (head + tail) >> 1;
        if (rmq(mid + 1, x) >= len) tail = mid;
        else head = mid;
    }
    if (rmq(head + 1, x) >= len) ans.first = head;
    else ans.first = tail;
    head = x, tail = n;
    while (head < tail - 1) {
        int mid = (head + tail) >> 1;
        if (rmq(x + 1, mid) >= len) head = mid;
        else tail = mid;
    }
    if (rmq(x + 1, tail) >= len) ans.second = tail;
    else ans.second = head;
    return ans;
}

int main() {
    init();
    int n, q;
    scanf("%d%d", &n, &q);
    int p = 0;
    for (int i = 1; i <= n; ++i) {
        start[i] = p + 1;
        static char S[N];
        scanf("%s", S);
        len[i] = strlen(S);
        for (int j = 0; j < len[i]; ++j) {
            str[++p] = S[j];
            mark[p] = i;
        }
        str[++p] = i + 1000;
        mark[p] = i;
    }
    suffix(p);
    build(1, 1, p);
    for (int j = 1; j < 20; ++j)
        for (int i = 1; i + (1 << j) - 1 <= p; ++i) {
            int y = i + (1 << (j - 1));
            height[j][i] = min(height[j - 1][i], height[j - 1][y]);
        }
    for (int i = 1; i <= q; ++i) {
        int L, R, k;
        pair<int, int> tmp;
        scanf("%d%d%d", &L, &R, &k);
        tmp = find(rank[start[k]], p, len[k]);
        printf("%d\n", query(1, 1, p, tmp.first, tmp.second, L, R));
    }
    return 0;
}
