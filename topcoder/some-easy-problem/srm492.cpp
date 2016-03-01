#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int x[100];

struct Point {
    int x, y;

    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    };
    
    int operator * (const Point &a) const {
        return x * a.y - a.x * y;
    }
};

class TimeTravellingGardener {
public:
    int determineUsage(vector <int> dis, vector <int> h) {
        int n = h.size();
        for (int i = 0; i + 1 < n; ++i)
            x[i + 1] = x[i] + dis[i];
        int ans = n - 1;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                Point S0 = (Point){x[i], h[i]};
                Point S1 = (Point){x[j], h[j]};
                if (((Point){x[0], 0} - S1) * (S0 - S1) > 0)
                    continue;
                if (((Point){x[n - 1], 0} - S0) * (S1 - S0) < 0)
                    continue;
                int res = n, flag = 0;
                for (int k = 0; k < n; ++k) {
                    Point C = (Point){x[k] - x[i], h[k] - h[i]};
                    if (C * (S1 - S0) == 0)
                        --res;
                    else {
                        if (C * (S1 - S0) > 0) flag = 1;
                    }
                }

                if (!flag) ans = min(ans, res);
            }
        return ans;
    }
};
