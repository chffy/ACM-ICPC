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

const int N = 1e5 + 5;

int bo[N];

class PerfectPermutation {
public:
    int reorder(vector <int> P) {
        int n = P.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (!bo[i]) {
                ++ans;
                int x = i;
                while (!bo[x]) {
                    bo[x] = 1;
                    x = P[x];
                }
            }
        if (ans == 1) ans = 0;
        return ans;
    }
};
