#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cmath>
using namespace std;

pair<int, int> die[105];

bitset<2501> f[105][55];

class KingdomAndDice {
public:
    double newFairness(vector <int> firstDie, vector <int> secondDie, int X) {
        int r = 0, n = firstDie.size(), zn = 0;
        for (int i = 0; i < n; ++i) {
            if (firstDie[i] == 0) ++zn;
            else die[++r] = make_pair(firstDie[i], 0);
            die[++r] = make_pair(secondDie[i], 1);
        }
        sort(die + 1, die + 1 + r);
        die[0] = make_pair(-1, 0);
        die[++r] = make_pair(X + 1, 0);
        for (int i = 1; i <= r; ++i)
            die[i].second += die[i - 1].second;
        f[0][0][0] = 1;
        for (int i = 0; i < r; ++i) 
            for (int j = 0; j <= zn; ++j)
                if (f[i][j].count() > 0) {
                    int fm = min(die[i + 1].first - die[i].first -1, zn - j);
                    for (int k = 0; k <= fm; ++k)
                        f[i + 1][j + k] |= f[i][j] << (k * die[i].second);
                }
        int win = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (firstDie[i] > secondDie[j]) ++win;
        double p = 10;
        for (int i = 0; i <= zn; ++i)
            for (int j = 0; j <= n * n; ++j)
                if (f[r][i][j]) {
                    int tmp = win + j;
                    double p1 = tmp * 1.0 / (n * n); 
                    double tmp1 = fabs(p - 0.5), tmp2 = fabs(p1 - 0.5);
                    if (fabs(tmp1 - tmp2) < 1e-9) p = min(p1, p);
                    else if (tmp2 < tmp1) p = p1;
                }
        return p;
    }
};
