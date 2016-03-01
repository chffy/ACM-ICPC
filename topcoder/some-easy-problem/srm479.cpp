#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;

class TheCoffeeTimeDivOne {
public:
    LL find(int n, vector <int> tea) {
        sort(tea.begin(), tea.end());
        int m = tea.size();
        LL ans = 4 * n;
        for (int i = m - 1; i >= 0; --i) {
            int j = i;
            while (i - j + 1 < 7 && j > 0) {
                --j;
            }
            ans += tea[i] * 2 + 47;
            i = j;
        }
        for (int i = n, k = m - 1; i > 0; --i) {
            int j = i;
            while (k > 0 && tea[k - 1] >= i) --k;
            int sum = (i != tea[k]);
            if (sum == 0) continue;
            while (sum < 7 && j > 1) {
                --j;
                while (k > 0 && tea[k - 1] >= j) --k;
                sum += (j != tea[k]);
            }
            if (sum > 0)
                ans += i * 2 + 47;
            i = j;
        }
        return ans;
    }
};
