#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;
int num[1000];

class Badgers {
public:
    int feedMost(vector <int> hunger, vector <int> greed, int totalFood) {
        int n = hunger.size();
        int ans = n;
        while (ans > 0) {
            int res = 0;
            for (int i = 0; i < n; ++i)
                num[i] = hunger[i] + (ans - 1) * greed[i];
            sort(num, num + n);
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                res += num[i];
                if (res > totalFood) break;
                ++cnt;
            }
            if (cnt >= ans) break;
            --ans;
        }
        return ans;
    }
};
