#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;

const int N = 305;

int rx[N], bx[N], by[N];

int gett(vector<string> x, int rx[]) {
    string S = "";
    for (int i = 0; i < x.size(); ++i)
        S += x[i];
    int p = 0, n = 0;
    while (p < S.size()) {
        rx[n] = 0;
        while (p < S.size() && isdigit(S[p])) {
            rx[n] = rx[n] * 10 + S[p] - '0';
            ++p;
        }
        ++n;
        if (p < S.size() && !isdigit(S[p])) ++p;
    }
    return n;
}

LL f[605], fl[605];
int b[605], r;
int xx, yy;
pair<int, int> h[605];

LL xc(LL x1, LL y1, LL x2, LL y2) {
    return x1 * y2 - x2 * y1;
}

int cmp(pair<int, int> a, pair<int, int> b) {
    return xc(a.first - xx, a.second - yy, b.first - xx, b.second - yy) > 0;
}

void add(int x, LL s, LL f[]) {
    while (x <= r) {
        f[x] += s;
        x += x & -x;
    }
}

LL find(int x, LL f[]) {
    LL ans = 0;
    while (x > 0) {
        ans += f[x];
        x -= x & -x;
    }
    return ans;
}

class Ear {
public:
    LL getCount(vector <string> redX, vector <string> blueX, vector <string> blueY) {
        int n = gett(redX, rx);
        int m = gett(blueX, bx);
        int m0 = gett(blueY, by);
        assert(n <= 300);
        assert(m <= 300);
        assert(m0 == m);
        sort(rx, rx + n);
        r = 0;
        for (int i = 0; i < n; ++i) {
            b[++r] = rx[i];
        }
        for (int i = 0; i < m; ++i) {
            b[++r] = bx[i];
        }
        sort(b + 1, b + 1 + r);
        r = unique(b + 1, b + r + 1) - b - 1;
        LL ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (bx[j] > rx[i]) {
                    memset(f, 0, sizeof(f));
                    memset(fl, 0, sizeof(fl));
                    int p = 0;
                    xx = bx[j], yy = by[j];
                    for (int k = 0; k < m; ++k)
                        if (xc(rx[i] - xx, -yy, bx[k] - xx, by[k] - yy) > 0) {
                            h[p++] = make_pair(bx[k], by[k]);
                        }
                    sort(h, h + p, cmp);
                    int L = 0;
                    LL sum = 0;
                    for (int k = i + 1; k < n; ++k) {
                        int tmp1 = lower_bound(b + 1, b + 1 + r, rx[k]) - b;
                        if (rx[k] <= bx[j]) {
                            add(tmp1, 1, f);
                            continue;
                        }
                        while (L < p && xc(h[L].first - xx, h[L].second - yy,
                                           rx[k] - xx, -yy) > 0) {
                            int tmp2 = lower_bound(b + 1, b + 1 + r, h[L].first) - b;
                            sum += find(tmp2 - 1, f) * (find(r, f) - find(tmp2, f));
                            add(tmp2, find(tmp2 - 1, f), fl);
                            ++L;
                        }
                        ans += sum;
                        sum += find(tmp1 - 1, fl);
                        add(tmp1, 1, f);
                    }
                }
        return ans;
    }
};
