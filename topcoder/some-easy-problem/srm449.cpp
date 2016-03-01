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

int sqrt_int(int x) {
    int y = sqrt(x);
    while (y * y < x) ++y;
    if (y * y != x) return -1;
    else return y;
}

void get_pr(int A, vector<pair<int, int> > &pr) {
    for (int i = 0; i * i <= A; ++i) {
        int x = A - i * i;
        int y = sqrt_int(x);
        if (y != -1) pr.push_back(make_pair(i, y));
    }
}

class MaxTriangle {
public:
    double calculateArea(int A, int B) {
        vector<pair<int, int> > prA, prB;
        get_pr(A, prA);
        get_pr(B, prB);
        if (prA.empty() || prB.empty()) return -1;
        double ans = 0;
      //  for (auto x : prA) printf("%d %d\n", x.first, x.second);
        for (auto x : prA)
            for (auto y : prB) 
                ans = max(ans, ((double)x.first * y.second + (double)x.second * y.first) / 2);
        return ans;
    }
};
