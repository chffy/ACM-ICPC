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

int dp[2][1005][2];

void updata(int &x, int y) {
    x = min(x, y);
}

class PouringWater {
public:
    int getMinBottles(int N, int K) {
        memset(dp, 63, sizeof(dp));
        int cur = 0, nex = 1, t = 1;
        dp[cur][0][0] = 0;
        while (N > 0) {
            memset(dp[nex], 63, sizeof(dp[nex]));
            for (int i = 0; i <= K; ++i)
                for (int j = 0; j < 2; ++j) {
                    int s = (N & 1) + j;
                    if (s % 2 == 0) {
                        updata(dp[nex][i][s >> 1], dp[cur][i][j]);
                    }
                    else {
                        updata(dp[nex][i + 1][s >> 1], dp[cur][i][j]);
                        updata(dp[nex][i][(s + 1) >> 1], dp[cur][i][j] + t);
                    }
                }
            t <<= 1;
            swap(cur, nex);
        }
        int ans = 1 << 30;
        for (int i = 0; i <= K; ++i) {
            ans = min(ans, dp[cur][i][0]);
            if (i < K) ans = min(ans, dp[cur][i][1]);
        }
        return ans;
    }
};
