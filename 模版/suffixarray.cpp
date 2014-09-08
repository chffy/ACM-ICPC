int height[N], rank[N], sa[N];

namespace Suffixarray {

    int sum[N], rank1[N], sb[N], rank0[N];

    void calc_suffix(int n) {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; ++i) ++sum[str[i]];
        for (int i = 1; i < N; ++i) sum[i] += sum[i - 1];
        for (int i = 1; i <= n; ++i) sa[sum[str[i]]--] = i;
        for (int i = 1, p = 1; i <= n; ++i) {
            if (i > 1 && str[sa[i]] != str[sa[i - 1]]) ++p;
            rank[sa[i]] = p;
        }
        for (int j = 1; rank[sa[n]] != n; j <<= 1) {
            memset(sum, 0, sizeof(int) * (n + 1));
            memcpy(sb, sa, sizeof(int) * (n + 1));
            memcpy(rank0, rank, sizeof(int) * (n + 1));
            for (int i = 1; i <= n; ++i)
                rank1[i] = (i <= n - j) ? rank[i + j] : 0;
            for (int i = 1; i <= n; ++i) sum[rank[i]]++;
            for (int i = 2; i <= n; ++i) sum[i] += sum[i - 1];
            for (int i = n; i; --i)
                if (sb[i] > j) 
                    sa[sum[rank[sb[i] - j]]--] = sb[i] - j;
            for (int i = n - j + 1; i <= n; ++i)
            sa[sum[rank[i]]--] = i;
            for (int i = 1, p = 0; i <= n; ++i) {
                if (i == 1 || rank1[sa[i]] != rank1[sa[i - 1]]
                    || rank0[sa[i]] != rank0[sa[i - 1]]) ++p;
                rank[sa[i]] = p;
            }
        }
    }

    void calc_height(int n) {
        memset(height, 0, sizeof(int) * (n + 1));
        for (int i = 1, p = 0; i <= n; ++i) {
            if (rank[i] == 1) continue;
            int j = sa[rank[i] - 1];
            while (i + p <= n && j + p <= n && str[i + p] == str[j + p])
                ++p;
            height[rank[i]] = p;
            if (p) --p;
        }
    }

    void solve(int n) {
        calc_suffix(n);
        calc_height(n);
    }
};
