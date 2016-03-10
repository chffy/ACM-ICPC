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

int sqr(int x) {
    return x * x;
}

class CirclesCountry {
public:
    
    int leastBorders(vector <int> X, vector <int> Y, vector <int> R, int x1, int y1, int x2, int y2) {
        int n = X.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int z1 = 0, z2 = 0;
            z1 = ((sqr(X[i] - x1) + sqr(Y[i] - y1)) < sqr(R[i]));
            z2 = ((sqr(X[i] - x2) + sqr(Y[i] - y2)) < sqr(R[i]));
            if (z1 != z2) ++ans;
        }
        return ans;
    }
};
