#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double pi = acos(-1.0);

pair<double, double> P[100];
double C[200];

class LaserShooting {
public:
    double numberOfHits(vector <int> x, vector <int> y1, vector <int> y2) {
        int n = x.size();
        int m = 0;
        for (int i = 0; i < n; ++i) {
            P[i].first = atan2(y1[i], x[i]);
            P[i].second = atan2(y2[i], x[i]);
            if (P[i].first > P[i].second) swap(P[i].first, P[i].second);
            C[m++] = P[i].first;
            C[m++] = P[i].second;
        }
        sort(C, C + m);
        double ans = 0;
        for (int i = 0; i + 1 < m; ++i) {
            int ret = 0;
            for (int j = 0; j < n; ++j)
                if (P[j].first <= C[i] && P[j].second >= C[i + 1])
                    ++ret;
            ans += ret * (C[i + 1] - C[i]);
        }
        ans /= pi;
        return ans;
    }
};
