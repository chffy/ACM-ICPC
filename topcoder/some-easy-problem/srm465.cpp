#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

typedef long long LL;

double sqr(double x) {
    return x * x;
}

class TurretPlacement {
public:
    LL count(vector <int> x, vector <int> y) {
        int n = x.size();
        LL ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                double len = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j])) * 2;
                int t = floor(len + (1e-9));
                ans += (LL)t * t - (LL)t * (t + 1) / 2;
            }
        return ans;
    }
};
