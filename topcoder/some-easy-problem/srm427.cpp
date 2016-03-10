#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

class DesignCalendar {
public:
    int shortestPeriod(int d, int y) {
        if (y % d == 0) return 1;
        int t = y % d;
        int k = __gcd(t, d);
        int ans = d / k;
        return ans;
    }
};
