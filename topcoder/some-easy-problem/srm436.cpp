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

int num[100];
typedef long long LL;

LL xc(LL x1, LL y1, LL x2, LL y2) {
    return x1 * y2 - x2 * y1;
}

class BestView {
public:
    int numberOfBuildings(vector <int> h) {
        int n = h.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                int flag = 1;
                for (int k = i + 1; k < j && flag; ++k)
                    if (xc(k - i, h[k] - h[i], j - i, h[j] - h[i]) <= 0) flag = 0;
                num[i] += flag;
                num[j] += flag;
            }
        int ans = 0;
        for (int i = 0; i < n; ++i) ans = max(ans, num[i]);
        return ans;
    }
};
