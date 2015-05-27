#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
using namespace std;

typedef long long LL;

pair<int, int> p[50], q[50];

const double esp = 1e-10;

class RangeSquaredSubsets {
public:
    LL countSubsets(int nlow, int nhigh, vector <int> x, vector <int> y) {
        int n = x.size();
        for (int i = 0; i < n; ++i)
            p[i] = make_pair(x[i], y[i]);
        sort(p, p + n);
        set<LL> ext;
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                int L = p[j].first - p[i].first, R = nhigh;
                if (i > 0 && p[i].first == p[i - 1].first)
                    continue;
                if (j + 1 < n && p[j].first == p[j + 1].first)
                    continue;
                L = max(L, nlow);
                if (i > 0 && j + 1 < n) {
                    R = min(R, p[j + 1].first - p[i - 1].first - 1);
                }
                int m = 0;
                for (int k = i; k <= j; ++k)
                    q[m++] = make_pair(p[k].second, k);
                sort(q, q + m);
                for (int k = 0; k < m; ++k) {
                    LL mask = 0;
                    for (int l = k; l < m; ++l) {
                        mask |= 1LL << q[l].second;
                        if (l + 1 < m && q[l].first == q[l + 1].first)
                            continue;
                        if (k > 0 && q[k].first == q[k - 1].first)
                            continue;
                        int L1 = q[l].first - q[k].first, R1 = 1 << 30;
                        if (k > 0 && l + 1 < m) {
                            R1 = q[l + 1].first - q[k - 1].first - 1;
                        }
                        if (max(L1, L) <= min(R1, R)) {
                            ext.insert(mask);
                        }
                    }
                }
            }
        return (LL)ext.size();
    }
};
