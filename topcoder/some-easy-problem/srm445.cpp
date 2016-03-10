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

class TheNewHouseDivOne {
public:
    double distance(vector <int> x, vector <int> y, int K) {
        int n = x.size();
        for (int i = 0; i < n; ++i) {
            int tx = x[i], ty = y[i];
            x[i] = tx + ty;
            y[i] = tx - ty;
        }
        double ans = 1e60;
        for (int i = -100; i <= 100; ++i)
            for (int j = -100; j <= 100; ++j) {
                vector<int> Q;
                for (int l = 0; l < n; ++l)
                    if (x[l] >= i && y[l] >= j)
                        Q.push_back(max(x[l] - i, y[l] - j));
                sort(Q.begin(), Q.end());
                if (Q.size() < K) continue;
                ans = min(ans, (double)Q[K - 1] / 2);
            }
        return ans;
    }
};
