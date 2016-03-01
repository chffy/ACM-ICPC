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

double pos[100];
int d[100];

class BouncingBalls {
public:
    double expectedBounces(vector <int> x, int T) {
        int n = x.size();
        sort(x.begin(), x.end());
        double ans = 0;
        for (int mask = 0; mask < 1 << n; ++mask) {
            for (int i = 0; i < n; ++i) {
                if (mask >> i & 1) d[i] = 1;
                else d[i] = -1;
                pos[i] = x[i];
            }
            int num = 0;
            double time = 0;
            while (1) {
                double mark = 1e40;
                int t = -1;
                for (int i = 0; i + 1 < n; ++i)
                    if (d[i] == 1 && d[i + 1] == -1) {
                        double tmp = (pos[i + 1] - pos[i]) / 2.0;
                        if (tmp < mark) {
                            mark = tmp;
                            t = i;
                        }
                    }
                if (time + mark > T + (1e-9)) break;
                for (int i = 0; i < n; ++i)
                    pos[i] += mark * d[i];
                ++num;
                swap(d[t], d[t + 1]);
                time += mark;
            }
            ans += (double)num / (1 << n);
        }
        return ans;
    }
};
