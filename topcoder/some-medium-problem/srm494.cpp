#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;

class AlternatingLane {
public:
    double expectedBeauty(vector <int> low, vector <int> h) {
        int n = low.size();
        double ans = 0;
        for (int i = 0; i + 1 < n; ++i) {
            double res = 0;
            int tot = h[i + 1] - low[i + 1] + 1; 
            for (int j = low[i]; j <= h[i]; ++j) {
                int l = max(j, low[i + 1]);
                int r = h[i + 1];
                if (l <= r) {
                    res += (((LL)r * (r + 1) / 2 - (LL)l * (l - 1) / 2) - (LL) j * (r - l + 1)) * 1.0 / tot;
                }
                l = low[i + 1];
                r = min(h[i + 1], j);
                if (l <= r) {
                    res -= (((LL)r * (r + 1) / 2 - (LL)l * (l - 1) / 2) - (LL) j * (r - l + 1)) * 1.0 / tot;
                }
            }
            res /= h[i] - low[i] + 1;
            ans += res;
        }
        return ans;
    }
};

