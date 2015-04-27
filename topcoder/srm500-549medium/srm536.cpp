#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
using namespace std;

typedef long long LL;

class RollingDiceDivOne {
public:
    LL mostLikely(vector <int> dice) {
        int n = dice.size();
        LL L = 0, R = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            --dice[i];
            if (dice[i] >= sum) {
                L = sum, R = dice[i];
            }
            else if (L + dice[i] <= R) {
                L += dice[i];
            }
            else {
                L = (sum + dice[i]) / 2;
                R = sum + dice[i] - L;
                //cout << 1 << endl;
            }
            sum += dice[i];
           // printf("%lld %lld\n", L, sum - R);
        }
        return L + n;
    }
};
