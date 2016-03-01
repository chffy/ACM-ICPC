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

class NotTwo {
public:
    int maxStones(int w, int h) {
        int ans = 0;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) {
                int num[2];
                num[0] = num[1] = 0;
                for (int k = i; k < w; k += 2)
                    for (int l = j; l < h; l += 2)
                        num[(k / 2 + l / 2) & 1]++;
                ans += max(num[0], num[1]);
            }
        return ans;
    }
};
